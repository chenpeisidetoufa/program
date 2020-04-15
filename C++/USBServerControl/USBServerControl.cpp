#include "USBServerControl.h"
#include <QCoreApplication>
#include <QSettings>
#include <QProcess>
#include <QtDebug>

extern void WINAPI GYCServiceHandler(DWORD dwOpCode);

USBServerControl::USBServerControl(QObject *parent)
{
	qDebug() << "Entry.";
	m_bStopThread = false;

	ReadConfig();

	qDebug() << "Exit.";
}

USBServerControl::~USBServerControl()
{
	Quit();
}

void USBServerControl::Start()
{
	m_bStopThread = false;
	start();
}

void USBServerControl::Quit()
{
	m_bStopThread = true;
	quit();
	wait();
}

void USBServerControl::ReadConfig()
{
	qDebug() << "Entry.";
	QString strAppPath = QCoreApplication::applicationDirPath();
	qDebug() << "USBReadServerPath = " << strAppPath;

	QString strFile = strAppPath + "/set.ini";
	QSettings set(strFile, QSettings::IniFormat);
	set.setIniCodec("GB18030");
	set.beginGroup("SERVERADDRESS");
	m_strIP = set.value("ip", "127.0.0.1").toString();
	m_strPort = set.value("port", "8090").toString();
	set.endGroup(); 
	
	set.beginGroup("OTHER");
	m_debug = set.value("debug", false).toBool();
	set.endGroup();
	qDebug() << "Exit.";
}

void USBServerControl::run()
{
	while (!m_bStopThread)
	{
		QProcess process;
		process.start("tasklist.exe");
		if (process.waitForFinished())
		{
			QByteArray result = process.readAllStandardOutput();
			if (!result.contains(g_strServiceFile.toLocal8Bit()))
			{	
				GYCServiceHandler(QTSERVICE_STARTUP);
			}
		}
		QThread::msleep(5000);
	}
}
