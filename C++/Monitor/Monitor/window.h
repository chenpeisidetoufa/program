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

const QString strUserName = QStringLiteral("������");

//�����û����ݽṹ
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
	//�رմ����¼����ں�̨����
	void closeEvent(QCloseEvent *event) override;

private slots:
	//������� 100msִ��һ��
	void Run();
	//��ʱ���ݴ������ݿ⣬�����ʱ���ݣ������ԻƵ�ʵͲ���������
	void WriteDB();
	//��������һ��ʱ�����Ƶ�ʵͣ�����
	void showMessage(QSystemTrayIcon::MessageIcon Icon);
	//����������ͼ���¼�
	void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
	//��ʼ�����ݿ�����
	bool InitDatabase(QSqlDatabase &db, QString strDBFile, const QString strConnectString);
	//д�����ݿ�
	bool InsertData(QList<USERDATA>& userData);

private:
	//����������ͼ��Actions
	void createActions();
	//����������ͼ��
	void createTrayicon();
	
private:
	//��������ʱ��
	QTimer m_RunTime;
	//��ʱ����д�����ݿⶨʱ��
	QTimer m_DBTime;
	//���ݿ�����
	QSqlDatabase m_db;
	//������ͼ��
	QSystemTrayIcon *trayIcon;
	//�������˵�
	QMenu *trayIconMenu;
	//�˳�action
	QAction *quitAction;
	//m_listUserData��
	QMutex m_userDataListMutex;
	//������û������б�
	QList<USERDATA> m_listUserData;
private:
	Ui::WindowClass ui;
};

#endif // WINDOW_H
