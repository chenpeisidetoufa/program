#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDomDocument>
#include <QMap>

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
    void on_pushButton_Save_clicked();

    void on_listWidget_Read_itemSelectionChanged();

    void on_pushButton_Read_clicked();

private:
    QString m_strPath;
    QMap<QString, double> m_mapIndex;
    QString m_strSchemeName;
    void FindXml();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
