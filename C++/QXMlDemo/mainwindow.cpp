#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDomProcessingInstruction>
#include <QDomText>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FindXml();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Save_clicked()
{
    if(ui->lineEdit_Name->text().isEmpty())
    {
        //加提示代码
        return;
    }

    QString strFile = QCoreApplication::applicationDirPath() + "/data/" +
            QString("%1.xml").arg(ui->lineEdit_Name->text());
    QFile file(strFile);
    QDir dir(QCoreApplication::applicationDirPath() + "/data");
    if(!dir.exists())
    {
        dir.mkpath(QCoreApplication::applicationDirPath() + "/data");
    }
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate |QIODevice::Text))
    {
        return ;
    }
    QTextStream out(&file);

    //XMl的创建，写入
    QDomDocument doc;
    doc.appendChild(doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\""));
    QDomElement root = doc.createElement("融合效能评估系统方案");
    doc.appendChild(root);
    QDomElement name = doc.createElement("方案名称");
    root.appendChild(name);
    QDomText no_text = doc.createTextNode(ui->lineEdit_Name->text());
    name.appendChild(no_text);

    QDomElement Index = doc.createElement("指标");
    root.appendChild(Index);
    Index.setAttribute("位置","0.5");
    Index.setAttribute("经度", "0.5");

    out.setCodec("UTF-8");
    doc.save(out,4,QDomNode::EncodingFromTextStream);
    file.close();
}

void MainWindow::FindXml()
{
    QString strPath = QCoreApplication::applicationDirPath() + "/data";
    QDir dir(strPath);
    if (!dir.exists())
    {
        dir.mkpath(QCoreApplication::applicationDirPath() + "/data");
        return;
    }
    QStringList disList = {"*.xml"};
    dir.setNameFilters(disList);
    QStringList strFileList;
    QString fileName;
    QFileInfoList fileInfoList = dir.entryInfoList();
    for (int i = 0; i < fileInfoList.count(); i++)
    {
        fileName = fileInfoList.at(i).fileName();
        strFileList.append(fileName);
    }
    ui->listWidget_Read->clear();
    ui->listWidget_Read->addItems(strFileList);
}

void MainWindow::on_listWidget_Read_itemSelectionChanged()
{
    QString strFilePath = QCoreApplication::applicationDirPath() + "/data";
    m_strPath = strFilePath + "/" + ui->listWidget_Read->currentItem()->text();
}

void MainWindow::on_pushButton_Read_clicked()
{
    if(m_strPath.isEmpty())
    {
        QMessageBox::critical(nullptr, QString("提示信息"), QString("请选择文件"));
    }

    //读取xml
    QFile file(m_strPath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        //QMessageBox::critical(nullptr, QString("提示信息"), QString("打开失败！/n文件不存在或损坏！"));
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        //qDebug() << "打开失败";
        return;
    }
    QDomElement root = doc.documentElement();
    if (root.tagName() == QString("融合效能评估系统方案"))
    {
        QDomElement elemet = root.firstChild().toElement();
        if(elemet.tagName() == QString("方案名称"))
        {
            m_strSchemeName = elemet.text();
        }
        elemet = elemet.nextSibling().toElement();
        if (elemet.tagName() == "指标")
        {
            auto attmap = elemet.attributes();
            for (int i = 0; i < attmap.count(); i++)
            {
                QString strIndex = attmap.item(i).nodeName();
                QString strValue = attmap.item(i).nodeValue();
                m_mapIndex[strIndex] = strValue.toDouble();
            }
        }
    }
    file.close();
    close();
}
