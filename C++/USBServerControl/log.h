#ifndef LOG_H
#define LOG_H

/**********************************************************************************
    作    者：王纳
    创建日期：date
    修改日期：
    功能描述：日志信息
    备    注：
***********************************************************************************/

#include <QCoreApplication>
#include <QMessageLogContext>
#include <QString>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include <QMutex>
#include <QThread>

//unsigned short GetProcessID()
//{
//#ifdef _MSC_VER
//    return GetCurrentProcessId();
//#else
//    return getpid();
//#endif
//}
//
//unsigned int GetCurrentThreadID()
//{
//#ifdef _MSC_VER
//    return GetCurrentThreadId();
//#else
//    return pthread_self();
//#endif
//}

void debugMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString strMsgType;
    QString newline = "\r\n";

    switch( type )
    {
        // 调试信息
        case QtDebugMsg:
			strMsgType = QString("DEBUG");
        break;
        case QtInfoMsg:
			strMsgType = QString("INFO ");
        break;
            // 警告信息
        case QtWarningMsg:
			strMsgType = QString("WARN ");
        break;
            // 严重错误
        case QtCriticalMsg:
			strMsgType = QString("ERROR");
        break;
            // 致命错误
        case QtFatalMsg:
			strMsgType = QString("FATAL");
        break;
    }

    QString strLogPath = QCoreApplication::applicationDirPath() + "/Log";
    QDir dir(strLogPath);
    if (!dir.exists(strLogPath))
    {
        dir.mkdir(strLogPath);
    }

    QString strFile = strLogPath;
    strFile.append(QString("/%1_%2.log").arg(QCoreApplication::applicationName()).arg(QDate::currentDate().toString("yyyyMMdd")));

    QFile log(strFile);
    log.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream cout(&log);
    cout.setCodec("UTF-8");
    QString message;
	QString threadText = QString("0x%1 ").arg(quintptr(QThread::currentThreadId()), 0, 16);
    message.append(threadText);
    message.append(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz" ));
    message.append("[").append(strMsgType).append("]:");
    message.append(msg);
    //message.append(", category = [");
    //message.append(context.category);
    //message.append("]");
    //message.append(", version = [");
    //message.append(QString::number(context.version, 10));
    //message.append("]");
    message.append("[").append(context.file).append("(").append(QString::number(context.line, 10)).append(")]");
    cout << message << newline;

    log.flush();
    log.close();

    mutex.unlock();
}

#endif // LOG_H
