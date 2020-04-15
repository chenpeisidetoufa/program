#include "MyTableView.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QHeaderView>

MyTableView::MyTableView(QWidget *parent)
    : QTableView(parent)
{
    setAcceptDrops(true);

    mLabel = new QLabel(this);
    mLabel->setFixedHeight(2);
    mLabel->setGeometry(1, 0, width(), 2);
    mLabel->setStyleSheet("border: 1px solid #8B7500;");
    mLabel->hide();

    mModel = NULL;
    mRowHeight = 30;
    mValidPress = false;
    mRowFrom = 0;
    mRowTo = 0;
}

void MyTableView::SetModel(QStandardItemModel *model)
{
    mModel = model;
    QTableView::setModel(model);
}

void MyTableView::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(e->pos());
        if (index.isValid())
        {
            mValidPress = true;
            mDragPoint = e->pos();
            mDragText = mModel->item(index.row(),1)->text();
            mDragPointAtItem = mDragPoint - QPoint(0,index.row()*mRowHeight);
            mRowFrom = index.row();
        }
    }
    QTableView::mousePressEvent(e);
}

void MyTableView::mouseMoveEvent ( QMouseEvent * e )
{
    if (!mValidPress)
    {
        return;
    }
    if (!(e->buttons() & Qt::LeftButton))
        return;

    if ((e->pos() - mDragPoint).manhattanLength()  < QApplication::startDragDistance())
        return;

    mLabel->show();

    DoDrag();           //开始拖拽，完成拖拽后才会继续往下走

    mLabel->hide();
    mValidPress = false;
}

void  MyTableView::dragEnterEvent ( QDragEnterEvent * e )
{
    if (e->mimeData()->hasText())
    {
        e->acceptProposedAction();
    }
    else
    {
        e->ignore();
        QTableView::dragEnterEvent(e);
    }
}

void  MyTableView::dragMoveEvent ( QDragMoveEvent * e )
{
    if(e->mimeData()->hasText())
    {
        int nCurRow = 0;
        QModelIndex index = indexAt(e->pos());
        if (index.isValid())
        {
            if(e->pos().y() - index.row()*mRowHeight >= mRowHeight/2)
            {
                nCurRow = index.row() + 1;
            }
            else
            {
                nCurRow = index.row();
            }
        }
        else
        {
            nCurRow = mModel->rowCount();
        }
//        if (nCurRow != mRowFrom)
        {
            mRowTo = nCurRow;
            mLabel->setGeometry(1, mRowTo*mRowHeight, width() - 2, 2);
        }
        e->acceptProposedAction();
        return;
    }

    e->ignore();
    QTableView::dragMoveEvent(e);
}

void  MyTableView::dropEvent ( QDropEvent * e )
{
    if(e->mimeData()->hasText())
    {
        if (mRowTo != mRowFrom)
        {
            MoveRow(mRowFrom, mRowTo);
        }
        e->acceptProposedAction();
        return;
    }

    e->ignore();
    QTableView::dropEvent(e);
}

void MyTableView::DoDrag()
{
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(mDragText);
    drag->setMimeData(mimeData);

    // 设置拖拽图片
    QPixmap drag_img(width(), mRowHeight);
    drag_img.fill(QColor(255,255,255,100));
    QPainter painter(&drag_img);
    painter.setPen(QColor(0, 0, 0, 200));
    painter.drawText(QRectF(40,0,width(),mRowHeight), mDragText, QTextOption(Qt::AlignVCenter));

    drag->setPixmap(drag_img);
    drag->setHotSpot(mDragPointAtItem);

    //***注意：此句会阻塞，进入drag的拖拽消息循环，会依次触发dragEnterEvent、dragMoveEvent、dropEvent消息
    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
    {
        // 确认移动操作
    }
}

void MyTableView::ResetOrder()
{
    for (int i = 0; i < mModel->rowCount(); i++)
    {
        mModel->item(i, 0)->setText( QString::number(i + 1) );
    }
}

void MyTableView::MoveRow(int from, int to)
{
    if (from == to)
    {
        return;
    }
    QStandardItem * item = mModel->item(from, 1);
    if (item)
    {
        QString strText = item->text();

        QList<QStandardItem*> items;
        QStandardItem* item0 = new QStandardItem("");
        QStandardItem* item1 = new QStandardItem(strText);
        items.append(item0);
        items.append(item1);
        item0->setTextAlignment(Qt::AlignCenter);

        //移动行思路：就是先在要移动到的位置新建同样内容的行，然后删除被移动的行
        mModel->insertRow(to, items);
        if (from < to)
        {
            mModel->removeRow(from);
            selectRow(to-1);
        }
        else
        {
            mModel->removeRow(from+1);
            selectRow(to);
        }
        ResetOrder();
        emit sigRowChange(mRowFrom,mRowTo);
    }
}
