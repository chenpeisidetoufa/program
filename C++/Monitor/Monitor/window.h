#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets/QDialog>
#include "ui_window.h"

#include <QSystemTrayIcon>
#include <QDialog>
#include <conio.h>
#include <windows.h>
#include <QTimer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlField>
#include <QtSql/QSqlError>
#include <QDateTime>
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QMutex>

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1 : 0)

const QString strUserName = QStringLiteral("杨亚龙");

//捕获用户数据结构
typedef struct _USERDATA
{
	_USERDATA()
	{
		Clear();
	}
	void Clear()
	{
		m_strName = "";
		m_strTime = "";
		m_strEvent = "";
	}
	void SetData(QString name, QString time, QString strEvent)
	{
		m_strName = name;
		m_strTime = time;
		m_strEvent = strEvent;
	}
	QString m_strName;
	QString m_strTime;
	QString m_strEvent;
}USERDATA, *pUSERDATA;

class Window : public QDialog
{
	Q_OBJECT

public:
	Window(QWidget *parent = 0);
	~Window();
protected:
	//关闭窗口事件，在后台运行
	void closeEvent(QCloseEvent *event) override;

private slots:
	//捕获操作 100ms执行一次
	void Run();
	//临时数据存入数据库，清空临时数据，若电脑活动频率低并发出警告
	void WriteDB();
	//若电脑在一段时间操作频率低，报警
	void showMessage(QSystemTrayIcon::MessageIcon Icon);
	//激活任务栏图标事件
	void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
	//初始化数据库连接
	bool InitDatabase(QSqlDatabase &db, QString strDBFile, const QString strConnectString);
	//写入数据库
	bool InsertData(QList<USERDATA>& userData);

private:
	//创建任务栏图标Actions
	void createActions();
	//创建任务栏图标
	void createTrayicon();
	
private:
	//捕获函数定时器
	QTimer m_RunTime;
	//临时数据写入数据库定时器
	QTimer m_DBTime;
	//数据库链接
	QSqlDatabase m_db;
	//任务栏图标
	QSystemTrayIcon *trayIcon;
	//任务栏菜单
	QMenu *trayIconMenu;
	//退出action
	QAction *quitAction;
	//m_listUserData锁
	QMutex m_userDataListMutex;
	//捕获的用户数据列表
	QList<USERDATA> m_listUserData;
private:
	Ui::WindowClass ui;
};

#endif // WINDOW_H
