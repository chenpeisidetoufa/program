#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitTableView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddDataAndSetAttribute(MyTableView * p, QStringList listStr)
{
    if (p == ui->tableView_RealTrack)
    {
        p->SetType(ENUM_REALTRACKTABLE);
    }
    else if (p == ui->tableView_RadarTrack)
    {
        p->SetType(ENUM_RADARTRACKTABLE);
    }
    else if (p == ui->tableView_FuseTrack)
    {
        p->SetType(ENUM_FUSETRACKTABLE);
    }
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QStringLiteral("序号")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QStringLiteral("内容")));
    for(int i=0;i<listStr.size();i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(i+1)));
        model->setItem(i, 1, new QStandardItem(listStr[i]));
        model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
    }
    p->SetModel(model);

    //设置样式
    p->setStyleSheet("QTableView {border: 1px solid gray;background: #E8E8E8;}\
                      QTableView::item{color:black;}\
                      QTableView::item:selected{color:black;background: #63B8FF;}");

    p->setColumnWidth(0,40);
    p->selectRow(0);
}

void MainWindow::InitTableView()
{
    MyTableView* pReal = ui->tableView_RealTrack;
    MyTableView* pRadar = ui->tableView_RadarTrack;
    MyTableView* pFuse = ui->tableView_FuseTrack;
    QStringList strList;
    strList<<"1001"<<"1002"<<"1003";
    AddDataAndSetAttribute(pReal, strList);
    strList.clear();
    strList<<"1001"<<"2001"<<"3001"<<"1002"<<"2002"<<"1003"<<"2003";
    AddDataAndSetAttribute(pRadar, strList);
    strList.clear();
    strList<<"1001"<<"1002"<<"1003";
    AddDataAndSetAttribute(pFuse, strList);
}

void MainWindow::on_tableWidget_Correlation_cellDoubleClicked(int row, int column)
{
    if(ui->tableWidget_Correlation->item(row, column) != nullptr)
    {
        ui->tableWidget_Correlation->takeItem(row, column);
    }
}
