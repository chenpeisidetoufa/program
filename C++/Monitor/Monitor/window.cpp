#include "window.h"
#include <QCloseEvent>
Window::Window(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	connect(&m_RunTime, SIGNAL(timeout()), this, SLOT(Run()));
	connect(&m_DBTime, SIGNAL(timeout()), this, SLOT(WriteDB()));
	m_RunTime.start(100);
	//TODO: ���ڸ�Ϊ10����һ�� ���Դ���10����
	//m_DBTime.start(1000*60*10);
	m_DBTime.start(1000*60*30);
	createActions();
	createTrayicon();
	connect(trayIcon, &QSystemTrayIcon::activated, this, &Window::iconActivated);

	trayIcon->show();
	setWindowTitle(QStringLiteral("�������ͣ�"));
	resize(400, 300);
}

Window::~Window()
{
	if (m_RunTime.isActive())
	{
		m_RunTime.stop();
	}
	if (m_DBTime.isActive())
	{
		m_DBTime.stop();
	}
}

void Window::closeEvent(QCloseEvent *event)
{
	if (trayIcon->isVisible())
	{
		hide();
		event->ignore();
	}
}

void Window::WriteDB()
{
	QMutexLocker locker(&m_userDataListMutex);
	//TODO: ��Ҫ�ڴ˶����ݿ����
	//TODO: �����ֵ���ȷ��
	if (m_listUserData.count() <= 50)
	{
		showMessage(QSystemTrayIcon::MessageIcon::Warning);
	}
	if (!m_listUserData.isEmpty())
	{
		if (!InsertData(m_listUserData))
		{
			qDebug() << "Error. InsertData";
			return;
		}
		m_listUserData.clear();
		ui.textEdit_monitor->clear();
	}
}

void Window::Run()
{
	QMutexLocker locker(&m_userDataListMutex);
	QDateTime timeTemp;
	QString str = "";
	int isEnter = 0;
	//�س�
	isEnter = GetKeyState(VK_RETURN);
	USERDATA userDataTemp;
	if (isEnter < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Enter��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Esc
	int isEsc = 0;
	isEsc = GetKeyState(VK_ESCAPE);
	if (isEsc < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Esc��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F1
	int isF1 = 0;
	isF1 = GetKeyState(VK_F1);
	if (isF1 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F1��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F2
	int isF2 = 0;
	isF2 = GetKeyState(VK_F2);
	if (isF2 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F2��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F3
	int isF3 = 0;
	isF3 = GetKeyState(VK_F3);
	if (isF3 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F3��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F4
	int isF4 = 0;
	isF4 = GetKeyState(VK_F4);
	if (isF4 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F4��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F5
	int isF5 = 0;
	isF5 = GetKeyState(VK_F5);
	if (isF5 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F5��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F6
	int isF6 = 0;
	isF6 = GetKeyState(VK_F6);
	if (isF6 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F6��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F7
	int isF7 = 0;
	isF7 = GetKeyState(VK_F7);
	if (isF7 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F7��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F8
	int isF8 = 0;
	isF8 = GetKeyState(VK_F8);
	if (isF8 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F8��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F9
	int isF9 = 0;
	isF9 = GetKeyState(VK_F9);
	if (isF9 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F9��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F10
	int isF10 = 0;
	isF10 = GetKeyState(VK_F10);
	if (isF10 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F10��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F11
	int isF11 = 0;
	isF11 = GetKeyState(VK_F11);
	if (isF11 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F11��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F12
	int isF12 = 0;
	isF12 = GetKeyState(VK_F12);
	if (isF12 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F12��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Home
	int isHome = 0;
	isHome = GetKeyState(VK_HOME);
	if (isHome < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Home��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//End
	int isEnd = 0;
	isEnd = GetKeyState(VK_END);
	if (isEnd < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("End��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Insert
	int isInsert = 0;
	isInsert = GetKeyState(VK_INSERT);
	if (isInsert < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Insert��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Delete
	int isDelete = 0;
	isDelete = GetKeyState(VK_DELETE);
	if (isDelete < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Delete��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Tilte
	int isTilte = 0;
	isTilte = GetKeyState(192);
	if (isTilte < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("~��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num0
	int isNum0 = 0;
	isNum0 = GetKeyState(48);
	if (isNum0 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num0��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num1
	int isNum1 = 0;
	isNum1 = GetKeyState(49);
	if (isNum1 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num1��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num2
	int isNum2 = 0;
	isNum2 = GetKeyState(50);
	if (isNum2 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num2��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num3
	int isNum3 = 0;
	isNum3 = GetKeyState(51);
	if (isNum3 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num3��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num4
	int isNum4 = 0;
	isNum4 = GetKeyState(52);
	if (isNum4 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num4��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num5
	int isNum5 = 0;
	isNum5 = GetKeyState(53);
	if (isNum5 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num5��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num6
	int isNum6 = 0;
	isNum6 = GetKeyState(54);
	if (isNum6 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num6��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num7
	int isNum7 = 0;
	isNum7 = GetKeyState(55);
	if (isNum7 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num7��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num8
	int isNum8 = 0;
	isNum8 = GetKeyState(56);
	if (isNum8 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num8��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Num9
	int isNum9 = 0;
	isNum9 = GetKeyState(57);
	if (isNum9 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Num9��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//-
	int isSub = 0;
	isSub = GetKeyState(189);
	if (isSub < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("-��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//+
	int isAdd = 0;
	isAdd = GetKeyState(187);
	if (isAdd < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("+��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Backspace
	int isBack = 0;
	isBack = GetKeyState(VK_BACK);
	if (isBack < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Backspace��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Tab
	int isTab = 0;
	isTab = GetKeyState(VK_TAB);
	if (isTab < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Tab��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//GapsLock
	int isGaps = 0;
	isGaps = GetKeyState(VK_CAPITAL);
	if (isGaps < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("GapsLock��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Shift
	int isShift = 0;
	isShift = GetKeyState(VK_SHIFT);
	if (isShift < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Shift��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Ctrl
	int isCtrl = 0;
	isCtrl = GetKeyState(VK_CONTROL);
	if (isCtrl < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Ctrl��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Win
	int isWin = 0;
	isWin = GetKeyState(VK_LWIN);
	if (isWin < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Win��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Alt
	int isAlt = 0;
	isAlt = GetKeyState(VK_MENU);
	if (isAlt < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Alt��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//�ո�
	int isSpace = 0;
	isSpace = GetKeyState(VK_SPACE);
	if (isSpace < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("�ո��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//PrtSc
	int isPrt = 0;
	isPrt = GetKeyState(VK_SNAPSHOT);
	if (isPrt < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Prtsc��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//��
	int isUp = 0;
	isUp = GetKeyState(VK_UP);
	if (isUp < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("�ϼ�");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//��
	int isDown = 0;
	isDown = GetKeyState(VK_DOWN);
	if (isDown < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("�¼�");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//��
	int isLet = 0;
	isLet = GetKeyState(VK_LEFT);
	if (isLet < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("���");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//��
	int isRig = 0;
	isRig = GetKeyState(VK_RIGHT);
	if (isRig < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("�Ҽ�");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//PgUp
	int isPgUp = 0;
	isPgUp = GetKeyState(VK_PRIOR);
	if (isPgUp < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("PgUp��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//PgDn
	int isPgDn = 0;
	isPgDn = GetKeyState(VK_NEXT);
	if (isPgDn < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("PgDn��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//< ,
	int isComma = 0;
	isComma = GetKeyState(188);
	if (isComma < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral(",��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//> .
	int isFullStop = 0;
	isFullStop = GetKeyState(190);
	if (isFullStop < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral(".��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//? /
	int isQueMark = 0;
	isQueMark = GetKeyState(191);
	if (isQueMark < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("/��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//: ;
	int isColon = 0;
	isColon = GetKeyState(186);
	if (isColon < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral(":��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//" '
	int isQuoMark = 0;
	isQuoMark = GetKeyState(222);
	if (isQuoMark < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("���ż�");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//{ [
	int isLBracket = 0;
	isLBracket = GetKeyState(219);
	if (isLBracket < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("[��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//} ]
	int isRBracket = 0;
	isRBracket = GetKeyState(221);
	if (isRBracket < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("]��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//\ |
	int isVerLine = 0;
	isVerLine = GetKeyState(220);
	if (isVerLine < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("|��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//A
	int isA = 0;
	isA = GetKeyState(65);
	if (isA < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("A��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//B
	int isB = 0;
	isB = GetKeyState(66);
	if (isB < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("B��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//C
	int isC = 0;
	isC = GetKeyState(67);
	if (isC < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("C��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//D
	int isD = 0;
	isD = GetKeyState(68);
	if (isD < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("D��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//E
	int isE = 0;
	isE = GetKeyState(69);
	if (isE < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("E��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//F
	int isF = 0;
	isF = GetKeyState(70);
	if (isF < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("F��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//G
	int isG = 0;
	isG = GetKeyState(71);
	if (isG < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("G��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//H
	int isH = 0;
	isH = GetKeyState(72);
	if (isH < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("H��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//I
	int isI = 0;
	isI = GetKeyState(73);
	if (isI < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("I��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//J
	int isJ = 0;
	isJ = GetKeyState(74);
	if (isJ < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("J��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//K
	int isK = 0;
	isK = GetKeyState(75);
	if (isK < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("K��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//L
	int isL = 0;
	isL = GetKeyState(76);
	if (isL < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("L��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//M
	int isM = 0;
	isM = GetKeyState(77);
	if (isM < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("M��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//N
	int isN = 0;
	isN = GetKeyState(78);
	if (isN < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("N��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//O
	int isO = 0;
	isO = GetKeyState(79);
	if (isO < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("O��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//P
	int isP = 0;
	isP = GetKeyState(80);
	if (isP < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("P��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Q
	int isQ = 0;
	isQ = GetKeyState(81);
	if (isQ < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Q��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//R
	int isR = 0;
	isR = GetKeyState(82);
	if (isR < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("R��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//S
	int isS = 0;
	isS = GetKeyState(83);
	if (isS < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("S��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//T
	int isT = 0;
	isT = GetKeyState(84);
	if (isT < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("T��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//U
	int isU = 0;
	isU = GetKeyState(85);
	if (isU < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("U��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//V
	int isV = 0;
	isV = GetKeyState(86);
	if (isV < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("V��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//W
	int isW = 0;
	isW = GetKeyState(87);
	if (isW < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("W��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//X
	int isX = 0;
	isX = GetKeyState(88);
	if (isX < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("X��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Y
	int isY = 0;
	isY = GetKeyState(89);
	if (isY < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Y��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//Z
	int isZ = 0;
	isZ = GetKeyState(90);
	if (isZ < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Z��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//NumLock
	int isNumLock = 0;
	isNumLock = GetKeyState(VK_NUMLOCK);
	if (isNumLock < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("NumLock��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���/
	int isPadSprit = 0;
	isPadSprit = GetKeyState(VK_DIVIDE);
	if (isPadSprit < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad/��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���*
	int isPadStar = 0;
	isPadStar = GetKeyState(VK_MULTIPLY);
	if (isPadStar < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad*��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���-
	int isPadSub = 0;
	isPadSub = GetKeyState(VK_SUBTRACT);
	if (isPadSub < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad-��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���+
	int isPadAdd = 0;
	isPadAdd = GetKeyState(VK_ADD);
	if (isPadAdd < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad+��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���0
	int isPad0 = 0;
	isPad0 = GetKeyState(VK_NUMPAD0);
	if (isPad0 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad0��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���1
	int isPad1 = 0;
	isPad1 = GetKeyState(VK_NUMPAD1);
	if (isPad1 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad1��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���2
	int isPad2 = 0;
	isPad2 = GetKeyState(VK_NUMPAD2);
	if (isPad2 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad2��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���3
	int isPad3 = 0;
	isPad3 = GetKeyState(VK_NUMPAD3);
	if (isPad3 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad3��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���4
	int isPad4 = 0;
	isPad4 = GetKeyState(VK_NUMPAD4);
	if (isPad4 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad4��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���5
	int isPad5 = 0;
	isPad5 = GetKeyState(VK_NUMPAD5);
	if (isPad5 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad5��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���6
	int isPad6 = 0;
	isPad6 = GetKeyState(VK_NUMPAD6);
	if (isPad6 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad6��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���7
	int isPad7 = 0;
	isPad7 = GetKeyState(VK_NUMPAD7);
	if (isPad7 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad7��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���8
	int isPad8 = 0;
	isPad8 = GetKeyState(VK_NUMPAD8);
	if (isPad8 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad8��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//���ּ���9
	int isPad9 = 0;
	isPad9 = GetKeyState(VK_NUMPAD9);
	if (isPad9 < 0)
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("Pad9��");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//������
	if (KEY_DOWN(MOUSE_MOVED))
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("������");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//����Ҽ�
	if (KEY_DOWN(MOUSE_EVENT))
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("����Ҽ�");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
	//����м�
	if (KEY_DOWN(MOUSE_WHEELED))
	{
		userDataTemp.Clear();
		timeTemp = QDateTime::currentDateTime();
		userDataTemp.m_strName = strUserName;
		userDataTemp.m_strTime = timeTemp.toString("yyyy-MM-dd HH:mm:ss:zzz");
		userDataTemp.m_strEvent = QStringLiteral("����м�");
		m_listUserData.append(userDataTemp);
		str.clear();
		str.append(userDataTemp.m_strTime);
		str.append("\\");
		str.append(userDataTemp.m_strEvent);
		ui.textEdit_monitor->append(str);
	}
}

void Window::showMessage(QSystemTrayIcon::MessageIcon Icon)
{
	QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(Icon);
	QString strTitle = "";
	QString strBody = "";
	if (msgIcon == QSystemTrayIcon::MessageIcon::Warning)
	{
		strTitle = QStringLiteral("���棡");
		strBody = QStringLiteral("���30���ӵ��ԻƵ�ʵͣ�");
		trayIcon->showMessage(strTitle, strBody, msgIcon, 5000);
	}
	if (msgIcon == QSystemTrayIcon::MessageIcon::Critical)
	{
		strTitle = QStringLiteral("����");
		strBody = QStringLiteral("�޷����ӷ�������");
		trayIcon->showMessage(strTitle, strBody, msgIcon, 5000);
	}
}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
		this->show();
		break;
	default:
		break;
	}
}

bool Window::InitDatabase(QSqlDatabase &db, QString strDBFile, const QString strConnectString)
{
	qDebug() << "Entry. InitDatabase";
	if (QSqlDatabase::contains(strConnectString))
	{
		db = QSqlDatabase::database(strConnectString);
	}
	else
	{
		db = QSqlDatabase::addDatabase("QSQLITE", strConnectString);
	}
	m_db.setDatabaseName(strDBFile);
	if (!db.isOpen())
	{
		if (!db.open())
		{
			QString strError = db.lastError().text();
			qDebug() << strError;
			return false;
		}
	}
	qDebug() << "Exit. InitDatabase";
	return true;
}

bool Window::InsertData(QList<USERDATA>& userData)
{
	qDebug() << "Entry. InsertData";
	//���ݿ�����
	QString strDBFile = QCoreApplication::applicationDirPath() + QString("/monitor.db");

	if (!InitDatabase(m_db, strDBFile, "monitor_connect"))
	{
		QString strError = m_db.lastError().text();
		qDebug() << strError;
		return false;
	}
	QSqlQuery query(m_db);
	//ƴװsql���
	if (!userData.isEmpty())
	{
		for (auto iter : userData)
		{
			QString name = iter.m_strName;
			QString time = iter.m_strTime;
			QString event = iter.m_strEvent;
			QString strSql = QStringLiteral("INSERT INTO UserMonitor (�û���,ʱ��,�¼�) VALUES('");
			strSql.append(name);
			strSql.append("', '");
			strSql.append(time);
			strSql.append("', '");
			strSql.append(event);
			strSql.append("');");

			//ִ��Sql���
			if (!query.exec(strSql))
			{
				QString strError = m_db.lastError().text();
				qDebug() << strError;
				return false;
			}
		}
	}
	qDebug() << "Exit. InsertData";
	return true;
}

void Window::createActions()
{
	quitAction = new QAction(QStringLiteral("�˳�"), this);
	connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void Window::createTrayicon()
{
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(quitAction);

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	QString strDBFile = ":/Window/Resources/monitor.jpg";
	QIcon icon(strDBFile);
	trayIcon->setIcon(icon);
	trayIcon->setVisible(true);
	setWindowIcon(icon);

	trayIcon->setToolTip("work assistant");
}
