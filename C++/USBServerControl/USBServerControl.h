#pragma once

#include <QThread>
#include <QTimer>
#include "windows.h"


//TODO 改成自己的程序
const QString g_strServiceFile = "test.exe";

const DWORD QTSERVICE_STARTUP = 256;

class USBServerControl : public QThread
{
	Q_OBJECT

public:
	USBServerControl(QObject *parent = Q_NULLPTR);
	~USBServerControl();
	void Start();
	void Quit();

private:
	void ReadConfig();

	virtual void run() override;

private:
	QString m_strIP;
	QString m_strPort;
	bool m_debug;

	bool m_bStopThread;
};
