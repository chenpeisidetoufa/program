#include "USBServerControl.h"
#include <QtWidgets/QApplication>
#include <QtDebug>
#include <QDir>
#include "log.h"
#include <windows.h>
#include <tlhelp32.h>
#include <UserEnv.h>
#include <strsafe.h>
#include <QProcess>

#pragma comment(lib, "Userenv.lib")

const QString g_strServiceName = "USB WebSocket Service";
SERVICE_STATUS_HANDLE g_handleServiceStatus = NULL;
DWORD g_dwStatus = SERVICE_STOPPED;

USBServerControl *g_pWorkerThread = nullptr;

void SetStatus(DWORD dwStatus)
{
	SERVICE_STATUS status;
	status.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	status.dwCurrentState = dwStatus;
	status.dwControlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP;
	status.dwWin32ExitCode = NO_ERROR;
	status.dwServiceSpecificExitCode = 0;
	status.dwCheckPoint = 1;
	status.dwWaitHint = 5000;
	SetServiceStatus(g_handleServiceStatus, &status);
	g_dwStatus = dwStatus;
}

//xindaida start
HANDLE GetProcessTokenDup(DWORD dwProcessId)
{
	HANDLE hProcess = NULL;
	HANDLE hToken = NULL;
	HANDLE hTokenDup = NULL;
	do
	{
		if (NULL == (hProcess = OpenProcess(MAXIMUM_ALLOWED, FALSE, dwProcessId)))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. OpenProcess";
			break;
		}
		if (!OpenProcessToken(hProcess,
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_SESSIONID | TOKEN_READ | TOKEN_WRITE,
			&hToken))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. OpenProcessToken";
			break;
		}

		if (!DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hTokenDup))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. DuplicateTokenEx";
			break;
		}

		// Completed
	} while (FALSE);
	if (NULL != hToken)
	{
		CloseHandle(hToken);
		hToken = NULL;
	}
	if (NULL != hProcess)
	{
		CloseHandle(hProcess);
		hProcess = NULL;
	}
	return hTokenDup;
}

DWORD GetProcessID(LPWSTR lpszProcessName, DWORD dwSessionId)
{
	qDebug() << "Entry.";
	DWORD dwProcessId = 0xFFFFFFFF;
	HANDLE hSnapshot = INVALID_HANDLE_VALUE;
	do
	{
		_ASSERT(NULL != lpszProcessName);
		if (NULL == lpszProcessName)
		{
			break;
		}
		hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hSnapshot)
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. CreateToolhelp32Snapshot";
			break;
		}

		PROCESSENTRY32 pe32 = { 0 };
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(hSnapshot, &pe32))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Process32First";
			break;
		}

		do
		{
			QString strszExeFile = QString::fromWCharArray(pe32.szExeFile);
			QString strszProcessName = QString::fromWCharArray(lpszProcessName);
			if (0 == strszExeFile.compare(strszProcessName, Qt::CaseInsensitive))
			{
				qDebug() << "OK, dwProcessId = " << dwProcessId;
				DWORD dwProcessSessionId = 0;
				if (ProcessIdToSessionId(pe32.th32ProcessID, &dwProcessSessionId)
					&& (dwSessionId == dwProcessSessionId))
				{
					dwProcessId = pe32.th32ProcessID;
					qDebug() << "OK, dwProcessId = " << dwProcessId;
					break;
				}
				qDebug() << "Not found. dwProcessId = " << dwProcessId;
			}
		} while (Process32Next(hSnapshot, &pe32));

		// Completed
	} while (FALSE);

	if (INVALID_HANDLE_VALUE != hSnapshot) { CloseHandle(hSnapshot); hSnapshot = INVALID_HANDLE_VALUE; }
	qDebug() << "Exit."; 
	return dwProcessId;
}

BOOL AdjustTokenDupPrivileges(HANDLE hTokenDup, LPCTSTR lpszPrivileges)
{
	BOOL bRet = FALSE;
	do
	{
		LUID luid = { 0 };
		if (!LookupPrivilegeValue(NULL, lpszPrivileges, &luid))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. LookupPrivilegeValue";
			break;
		}

		TOKEN_PRIVILEGES tp = { 0 };
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Luid = luid;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		// Adjust token privileges
		if (!AdjustTokenPrivileges(hTokenDup, FALSE, &tp, sizeof(tp), NULL, NULL))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. AdjustTokenPrivileges";
			break;
		}
		// Completed
		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

BOOL AdjustProcessTokenDup(HANDLE hTokenDup, DWORD dwSessionId)
{
	BOOL bRet = FALSE;
	do
	{
		if (NULL == hTokenDup) { break; }

		// Adjust Token Privileges
		if (!SetTokenInformation(hTokenDup, TokenSessionId, (LPVOID)&dwSessionId, sizeof(dwSessionId)))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. SetTokenInformation";
			break;
		}

		if (!AdjustTokenDupPrivileges(hTokenDup, SE_DEBUG_NAME))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Enable SE_DEBUG_NAME Privilege Failed!";
		}
		if (!AdjustTokenDupPrivileges(hTokenDup, SE_TCB_NAME))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Enable SE_TCB_NAME Privilege Failed!";
		}
		if (!AdjustTokenDupPrivileges(hTokenDup, SE_CHANGE_NOTIFY_NAME))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Enable SE_CHANGE_NOTIFY_NAME Privilege Failed!";
		}
		if (!AdjustTokenDupPrivileges(hTokenDup, SE_INCREASE_QUOTA_NAME))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Enable SE_INCREASE_QUOTA_NAME Privilege Failed!";
		}
		if (!AdjustTokenDupPrivileges(hTokenDup, SE_ASSIGNPRIMARYTOKEN_NAME))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Enable SE_ASSIGNPRIMARYTOKEN_NAME Privilege Failed!";
		}

		// Completed
		bRet = TRUE;
	} while (FALSE);
	return bRet;
}

// 创建交互式服务安装完成以后，启动UI的程序
BOOL LaunchApplication(LPCTSTR lpszExecute, LPCTSTR lpszCmdLine)
{
	qDebug() << "Entry. lpszExecute = [" << QString::fromWCharArray(lpszExecute) << "]";
	BOOL bRet = FALSE;
	HANDLE hUserTokenDup = NULL;
	LPVOID pEnv = NULL;
	do
	{
		DWORD dwSessionId = 0;
		if (0xFFFFFFFF == (dwSessionId = WTSGetActiveConsoleSessionId()))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. WTSGetActiveConsoleSessionId";
			break;
		}
		qDebug() << "dwSessionId = " << dwSessionId;
#define DEFAULT_WINLOGON_APPLICATION		(TEXT("winlogon.exe"))
#define DEFAULT_DEFAULT_APPLICATION		(TEXT("explorer.exe"))
		// 需要以explorer.exe进程的Token来创建Env环境块，否则以服务启动的App在打开文件路径的方面可能会遇到一些问题，比如最常见的是会访问C:\Windows\System32\config\systemprofile导致访问了错误的位置。

		DWORD dwWinlogonPid = 0;
		if (0xFFFFFFFF == (dwWinlogonPid = GetProcessID(DEFAULT_WINLOGON_APPLICATION, dwSessionId)))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Get Process ID Failed!";
			break;
		}
		qDebug() << "dwWinlogonPid = " << dwWinlogonPid;
		if (NULL == (hUserTokenDup = GetProcessTokenDup(dwWinlogonPid)))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Get Process Duplicate Token Failed!";
			break;
		}
		qDebug() << "hUserTokenDup = " << hUserTokenDup;
		if (!AdjustProcessTokenDup(hUserTokenDup, dwSessionId))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Adjust Process Token Failed!";
			break;
		}
		qDebug() << "Adjust Process Token Succeed!";
		HANDLE hDefaultTokenDup2 = NULL;
		DWORD dwDefaultPid = 0;
		if (0xFFFFFFFF == (dwDefaultPid = GetProcessID(DEFAULT_DEFAULT_APPLICATION, dwSessionId)))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Get Process ID Failed!";
			break;
		}
		qDebug() << "dwDefaultPid = " << dwDefaultPid;
		if (NULL == (hDefaultTokenDup2 = GetProcessTokenDup(dwDefaultPid)))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. Get Process Duplicate Token Failed!";
			break;
		}
		qDebug() << "hDefaultTokenDup2 = " << hDefaultTokenDup2;

		// Create Environment Block
		DWORD dwCreateFlags = NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE;
		if (CreateEnvironmentBlock(&pEnv, hDefaultTokenDup2, TRUE))
		{
			dwCreateFlags |= CREATE_UNICODE_ENVIRONMENT;
		}

		// Launch Process In The Client's Logon Session
		TCHAR szCmdLine[MAX_PATH] = { 0 };
		if (NULL != lpszCmdLine) { StringCchPrintf(szCmdLine, _countof(szCmdLine), TEXT("%s"), lpszCmdLine); }

#define DEFAULT_DESKTOP_WINSTA0				(TEXT("winsta0\\default"))

		PROCESS_INFORMATION pi = { 0 };
		STARTUPINFO si = { sizeof(STARTUPINFO) };
		si.lpDesktop = DEFAULT_DESKTOP_WINSTA0;

		if (!CreateProcessAsUser(hUserTokenDup,
			lpszExecute,
			szCmdLine,
			NULL,
			NULL,
			FALSE,
			dwCreateFlags,
			pEnv,
			NULL,
			&si,
			&pi))
		{
			DWORD errCode = GetLastError();
			qDebug() << "error. id = [" << errCode << "]. CreateProcessAsUser";
			break;
		}

		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		// Completed
		bRet = TRUE;
	} while (FALSE);

	if (NULL != pEnv)
	{
		DestroyEnvironmentBlock(pEnv);
		pEnv = NULL;
	}
	if (NULL != hUserTokenDup)
	{
		CloseHandle(hUserTokenDup);
		hUserTokenDup = NULL;
	}
	qDebug() << "Exit.";
	return bRet;
}

//xindaima end

//BOOL GetTokenByName(HANDLE &hToken, LPWSTR lpName)
//{
//	if (!lpName)
//	{
//		return FALSE;
//	}
//	HANDLE hProcessSnap = NULL;
//	PROCESSENTRY32 pe32 = { 0 };
//
//	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//	if (hProcessSnap == INVALID_HANDLE_VALUE)
//	{
//		return FALSE;
//	}
//	pe32.dwSize = sizeof(PROCESSENTRY32);
//	if (!Process32First(hProcessSnap, &pe32))
//	{
//		return FALSE;
//	}
//	
//	do
//	{
//		if (!wcscmp(_wcsupr(pe32.szExeFile), _wcsupr(lpName)))
//		{
//			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION,
//				FALSE, pe32.th32ProcessID);
//			BOOL bRet = OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken);
//			CloseHandle(hProcess);
//			CloseHandle(hProcessSnap);
//			return bRet;
//		}
//	} while (Process32Next(hProcessSnap, &pe32));
//	
//	CloseHandle(hProcessSnap);
//	return FALSE;
//}

//BOOL RunProcess(LPCWSTR lpImage)
//{
//	qDebug() << QString("Entry.lpImage = [%1]").arg(QString::fromWCharArray(lpImage));
//	if (!lpImage)
//	{
//		qDebug() << QString("Exit. lpImage is nullptr.");
//		return FALSE;
//	}
//	HANDLE hToken;
//	if (!GetTokenByName(hToken, TEXT("EXPLORER.EXE")))
//	{
//		qDebug() << QString("Exit. GetTokenByName");
//		return FALSE;
//	}
//	STARTUPINFO si;
//	PROCESS_INFORMATION pi;
//
//	ZeroMemory(&si, sizeof(STARTUPINFO));
//	si.cb = sizeof(STARTUPINFO);
//	si.lpDesktop = TEXT("winsta0\\default");
//	BOOL bResult = CreateProcessAsUser(hToken, lpImage, NULL, NULL, NULL,
//		FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
//	CloseHandle(hToken);
//	if (bResult)
//	{
//		qDebug() << QString("CreateProcessAsUser ok.");
//	}
//	else
//	{
//		DWORD errCode = GetLastError();
//		qDebug() << QString("CreateProcessAsUser false. result = [%1]").arg(errCode);
//	}
//	qDebug() << "Exit.";
//	return bResult;
//}

void WINAPI GYCServiceHandler(DWORD dwOpCode)
{
	qDebug() << QString("Entry. Handle operation code = [%1]").arg(dwOpCode);
	switch (dwOpCode)
	{
	case QTSERVICE_STARTUP: // QtService startup (called from WinMain when started)
	{
		SetStatus(SERVICE_START_PENDING);
		QString strControlFile = QCoreApplication::applicationDirPath() + "/" + g_strServiceFile;
		LaunchApplication(strControlFile.toStdWString().data(), nullptr);
		//RunProcess(strControlFile.toStdWString().data());
		SetStatus(SERVICE_RUNNING);
	}
	break;
	case SERVICE_CONTROL_STOP: // 1
	{
		SetStatus(SERVICE_STOP_PENDING);
		if (nullptr != g_pWorkerThread)
		{
			g_pWorkerThread->Quit();
		}
		//QProcess process;
		//process.startDetached("taskkill.exe /F /FI \"IMAGENAME eq USBReadServer.exe\"");
		SetStatus(SERVICE_STOPPED);
	}
	break;
	case SERVICE_CONTROL_PAUSE: // 2
	{
		SetStatus(SERVICE_PAUSE_PENDING);
		if (nullptr != g_pWorkerThread)
		{
			g_pWorkerThread->Quit();
		}
		SetStatus(SERVICE_PAUSED);
	}
	break;
	case SERVICE_CONTROL_CONTINUE: // 3
	{
		SetStatus(SERVICE_CONTINUE_PENDING);
		if (nullptr != g_pWorkerThread)
		{
			g_pWorkerThread->Start();
		}
		SetStatus(SERVICE_RUNNING);
	}
	break;
	case SERVICE_CONTROL_INTERROGATE: // 4
		break;
	case SERVICE_CONTROL_SHUTDOWN: // 5
	{
		// Don't waste time with reporting stop pending, just do it
		//QCoreApplication::postEvent(qApp, new QEvent(QEvent::Type(QEvent::User + dwOpCode)));
	}
	break;
	default:
	{
		if (dwOpCode >= 128 && dwOpCode <= 255) {
		}
		SetStatus(g_dwStatus);
	}
	break;
	}
	SetStatus(g_dwStatus);
	qDebug() << "Exit. handle.";
}

void WINAPI GYCServiceMain(DWORD dwArgc, wchar_t** lpszArgv)
{
	QStringList serviceArgs;
	for (DWORD i = 0; i < dwArgc; i++)
	{
		serviceArgs.append(QString::fromUtf16((unsigned short*)lpszArgv[i]));
	}
	QString strAppPath = QString::fromWCharArray(lpszArgv[0]);
	qDebug() << "strAppPath = " << strAppPath;
	// Register the control request handler
	g_handleServiceStatus = RegisterServiceCtrlHandler(lpszArgv[0], GYCServiceHandler);

	if (!g_handleServiceStatus) // cannot happen - something is utterly wrong
	{
		qCritical() << "The handle for Service Status is nullptr.";
	}
}

bool IsInstalledGYCService()
{
	bool result = false;
	// Open the Service Control Manager
	SC_HANDLE hSCM = OpenSCManager(0, 0, 0);
	if (hSCM)
	{
		// Try to open the service
		SC_HANDLE hService = OpenService(hSCM, (wchar_t*)g_strServiceName.utf16(), SERVICE_QUERY_CONFIG);

		if (hService)
		{
			result = true;
			CloseServiceHandle(hService);
		}
		CloseServiceHandle(hSCM);
	}
	return result;
}

bool InstallGYCService(QString strPath, QString strServiceDescription)
{
	bool result = false;
	// Open the Service Control Manager
	SC_HANDLE hSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hSCM)
	{
		DWORD dwStartType = SERVICE_AUTO_START;
		DWORD dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
		QDir dir(strPath);
		// Create the service
		SC_HANDLE hService = CreateService(hSCM, (wchar_t *)g_strServiceName.utf16(),
			(wchar_t *)g_strServiceName.utf16(),
			SERVICE_ALL_ACCESS,
			dwServiceType, // QObject::inherits ( const char * className ) for no inter active ????
			dwStartType, SERVICE_ERROR_NORMAL, (wchar_t *)dir.path().utf16(),
			0, 0, TEXT("RPCSS"), 0, 0);
		if (hService)
		{
			result = true;
			if (!strServiceDescription.isEmpty()) {
				SERVICE_DESCRIPTION sdesc;
				sdesc.lpDescription = (wchar_t *)strServiceDescription.toStdWString().data();
				ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &sdesc);
				SERVICE_FAILURE_ACTIONS sdBuf = { 0 };
				sdBuf.lpRebootMsg = NULL;
				sdBuf.dwResetPeriod = 3600 * 24;

				SC_ACTION action[3];

				action[0].Delay = 60 * 1000;
				action[0].Type = SC_ACTION_RESTART;
				action[1].Delay = 60 * 1000;
				action[1].Type = SC_ACTION_RESTART;
				action[2].Delay = 60 * 1000;
				action[2].Type = SC_ACTION_RESTART;

				sdBuf.cActions = 3;
				sdBuf.lpsaActions = action;
				sdBuf.lpCommand = NULL;
				ChangeServiceConfig2(hService, SERVICE_CONFIG_FAILURE_ACTIONS, &sdBuf);
				CloseServiceHandle(hService);
			}
			else
			{
				DWORD errCode = GetLastError();
				qDebug() << QString("Create service failed.[%1]").arg(errCode);
			}
		}
		CloseServiceHandle(hSCM);
	}
	else
	{
		DWORD errCode = GetLastError();
		qDebug() << QString("Open SCM failed.[%1]").arg(errCode);
	}
	return result;
}

bool UnInstallGYCService()
{
	bool result = false;
	// Open the Service Control Manager
	SC_HANDLE hSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hSCM) {
		SC_HANDLE hService = OpenService(hSCM, (wchar_t *)g_strServiceName.utf16(), DELETE);
		if (hService) {
			result = DeleteService(hService);
			if (result)
			{
				qDebug() << "Delete service succeed.";
			}
			else
			{
				DWORD errCode = GetLastError();
				qDebug() << QString("delete service failed.[%1]").arg(errCode);
			}
			CloseServiceHandle(hService);
		}
		else
		{
			DWORD errCode = GetLastError();
			qDebug() << QString("Open service failed.[%1]").arg(errCode);
		}
		CloseServiceHandle(hSCM);
	}
	else
	{
		DWORD errCode = GetLastError();
		qDebug() << QString("visit refused.[%1]").arg(errCode);
	}
	return result;
}

bool StartGYCService(DWORD dwNumServiceArgs, LPCWSTR *lpServiceArgVectors)
{
	bool result = false;
	// Open the Service Control Manager
	SC_HANDLE hSCM = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);
	if (hSCM)
	{
		SC_HANDLE hService = OpenService(hSCM, (wchar_t *)g_strServiceName.utf16(), SERVICE_START);
		if (hService)
		{
			result = ::StartService(hService, 0, nullptr);
			if (result)
			{
				qDebug() << "Start service succeed.";
			}
			else
			{
				DWORD errCode = GetLastError();
				qDebug() << QString("Start service failed.[%1]").arg(errCode);
			}
			CloseServiceHandle(hService);
		}
		else
		{
			DWORD errCode = GetLastError();
			qDebug() << QString("Open service failed.[%1]").arg(errCode);
		}
		CloseServiceHandle(hSCM);
	}
	else
	{
		DWORD errCode = GetLastError();
		qDebug() << QString("visit refused.[%1]").arg(errCode);
	}
	return result;
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	qInstallMessageHandler(debugMessageHandler);

	USBServerControl m;
	m.Start();
	g_pWorkerThread = &m;

	QStringList listArgs = QCoreApplication::arguments();
	//卸载方法
	//listArgs.append(QString("-uninstall"));
	if (listArgs.count() > 1 && 0 == listArgs.at(1).compare("-uninstall", Qt::CaseInsensitive))
	{
		UnInstallGYCService();
		return EXIT_SUCCESS;
	}
	if (!IsInstalledGYCService())
	{
		//安装服务
		InstallGYCService(listArgs.at(0), QStringLiteral("USB上位机服务程序"));
		//启动服务
		StartGYCService(0, nullptr);
	}

	SERVICE_TABLE_ENTRY arSvc[2];
	arSvc[0].lpServiceName = (wchar_t*)g_strServiceName.utf16();
	arSvc[0].lpServiceProc = GYCServiceMain;
	arSvc[1].lpServiceName = nullptr;
	arSvc[1].lpServiceProc = nullptr;

	if (!StartServiceCtrlDispatcher(arSvc))
	{
		DWORD errCode = GetLastError();
		qDebug() << QString("StartServiceCtrlDispatcher failed:[%1]").arg(errCode);
		return EXIT_FAILURE;
	}

	return a.exec();
}
