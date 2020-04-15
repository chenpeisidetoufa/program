#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QObject>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "common.h"

class MyTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    MyTableWidget(QWidget *parent = Q_NULLPTR);

protected:
    //拖拽响应事件
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void MoveToTable(QPoint pos, QString strTrack);
private:
    int mRowHeight;             //表格的行高
};

#endif // MYTABLEWIDGET_H
