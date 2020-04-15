#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MyTableView.h"
#include "MyTableWidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tableWidget_Correlation_cellDoubleClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    //初始化表格内容和样式
    void InitTableView();
    void AddDataAndSetAttribute(MyTableView * p = nullptr, QStringList listStr = QStringList());
};

#endif // MAINWINDOW_H
