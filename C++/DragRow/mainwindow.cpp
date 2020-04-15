#include "MyTableView.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitTable()
{
    MyTableView* t = ui->tableView;

    //设置各种属性
    t->horizontalHeader()->hide();	//隐藏列头(带列头的情况需要修改代码，重新计算高度偏移)
    t->verticalHeader()->hide();	//隐藏行头
    t->verticalHeader()->setDefaultSectionSize(30);         //默认列高度
    t->horizontalHeader()->setStretchLastSection(true);     //最后一列自适应宽度
    t->setEditTriggers(QTableView::NoEditTriggers);			//不能编辑
    t->setSelectionBehavior(QTableView::SelectRows);		//一次选中整行
    t->setSelectionMode(QTableView::SingleSelection);       //单行选中
    t->setAlternatingRowColors(true);                       //行间隔色
    t->setShowGrid(false);                                  //去掉网格线
    t->setFocusPolicy(Qt::NoFocus);                         //去掉item选中时虚线框

    //添加数据
    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QStringLiteral("序号")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QStringLiteral("内容")));
    QStringList strs;
    strs<<"111"<<"222"<<"333"<<"444"<<"AAA"<<"BBB"<<"CCC"<<"DDD";
    for(int i=0;i<strs.size();i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(i+1)));
        model->setItem(i, 1, new QStandardItem(strs[i]));
        model->item(i, 0)->setTextAlignment(Qt::AlignCenter);
    }
    t->SetModel(model);

    //设置样式
    t->setStyleSheet("QTableView {border: 1px solid gray;background: #E8E8E8;}\
                      QTableView::item{color:black;}\
                      QTableView::item:selected{color:black;background: #63B8FF;}");

    t->setColumnWidth(0,40);
    t->selectRow(0);
}
