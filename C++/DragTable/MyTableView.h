#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QMouseEvent>
#include "common.h"

class MyTableView : public QTableView
{
    Q_OBJECT
public:
    MyTableView(QWidget *parent = Q_NULLPTR);

    //此函数包装了自带的setModel，只是记录了model指针方便内部调用
    void SetModel(QStandardItemModel *model);
    void SetType(ENUMTABLEVIEW enum_type);

signals:

protected:
    //根据鼠标事件开启拖拽
    void mousePressEvent ( QMouseEvent * event ) ;
    void mouseMoveEvent(QMouseEvent *event);

private:
    void DoDrag();                      //执行拖拽
private:
    ENUMTABLEVIEW mEnum_TableView;
    QStandardItemModel *mModel;
    int mRowHeight;             //表格的行高

    bool mValidPress;           //在鼠标移动时，判断之前按下时是否是在有效行上
    QPoint mDragPoint;          //拖拽起点
    QString mDragText;          //拖拽过程中跟随鼠标显示的内容
    QPoint mDragPointAtItem;    //记录按下时鼠标相对该行的位置，在拖动过程中保持该相对位置
};

#endif // MYTABLEVIEW_H
