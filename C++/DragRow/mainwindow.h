#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //初始化表格内容和样式
    void InitTable();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
