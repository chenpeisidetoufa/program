#include "MyTableView.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QPainter>
#include <QHeaderView>

MyTableView::MyTableView(QWidget *parent)
    : QTableView (parent)
{
    mEnum_TableView = ENUM_NONETABLE;
    horizontalHeader()->hide(); //隐藏列头
    verticalHeader()->hide();	//隐藏行头
    verticalHeader()->setDefaultSectionSize(30);         //默认列高度
    horizontalHeader()->setStretchLastSection(true);     //最后一列自适应宽度
    setEditTriggers(QTableView::NoEditTriggers);			//不能编辑
    setSelectionBehavior(QTableView::SelectRows);		//一次选中整行
    setSelectionMode(QTableView::SingleSelection);       //单行选中
    setAlternatingRowColors(true);                       //行间隔色
    setShowGrid(false);                                  //去掉网格线
    setFocusPolicy(Qt::NoFocus);                         //去掉item选中时虚线框

    setAcceptDrops(true);
    mModel = nullptr;
    mRowHeight = 30;
    mValidPress = false;
}

void MyTableView::SetModel(QStandardItemModel *model)
{
    mModel = model;
    QTableView::setModel(model);
}

void MyTableView::SetType(ENUMTABLEVIEW enum_type)
{
    mEnum_TableView = enum_type;
}

void MyTableView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QModelIndex index = indexAt(event->pos());
        if (index.isValid())
        {
            mValidPress = true;
            mDragPoint = event->pos();
            mDragText = mModel->item(index.row(),1)->text();
            mDragPointAtItem = mDragPoint - QPoint(0,index.row()*mRowHeight);
        }
    }
    QTableView::mousePressEvent(event);
}

void MyTableView::mouseMoveEvent(QMouseEvent *event)
{
    if (!mValidPress)
    {
        return;
    }
    if (!(event->buttons() & Qt::LeftButton))
        return;
    if ((event->pos() - mDragPoint).manhattanLength()  < QApplication::startDragDistance())
        return;
    DoDrag();           //开始拖拽，完成拖拽后才会继续往下走
    mValidPress = false;
}

void MyTableView::DoDrag()
{
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    if(mEnum_TableView == ENUM_REALTRACKTABLE)
    {
        mimeData->setObjectName("RealTrack");
    }
    else if (mEnum_TableView == ENUM_RADARTRACKTABLE)
    {
        mimeData->setObjectName("RadarTrack");
    }
    else if (mEnum_TableView == ENUM_FUSETRACKTABLE)
    {
        mimeData->setObjectName("FuseTrack");
    }
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
