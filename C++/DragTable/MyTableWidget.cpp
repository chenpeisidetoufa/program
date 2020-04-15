#include "MyTableWidget.h"
#include <QHeaderView>
#include <QDrag>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDebug>
#include <QMessageBox>

const QString strSeparator = "/";

MyTableWidget::MyTableWidget(QWidget *parent)
    : QTableWidget (parent)
{
    setRowCount(10);     //设置行数为10
    setColumnCount(3);   //设置列数为3
    QStringList header;
    header<<"真值GPS航迹"<<"雷达航迹"<<"融合航迹";
    setHorizontalHeaderLabels(header);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionBehavior(QAbstractItemView::SelectItems);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setDefaultSectionSize(30);         //默认列高度
    setAlternatingRowColors(true);                       //行间隔色
    horizontalHeader()->setStyleSheet( "QHeaderView::section {background:#63B8FF;}");
    horizontalHeader()->setHighlightSections(false);

    setAcceptDrops(true);
    mRowHeight = 30;
}

void MyTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
        QTableWidget::dragEnterEvent(event);
    }
}

void MyTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasText())
    {
        QModelIndex Index = indexAt(event->pos());
        if(Index.isValid())
        {
            //qDebug()<<Index.row();
            int iColumn = Index.column();
            switch (iColumn)
            {
            case 0:
                if(event->mimeData()->objectName().compare("RealTrack") == 0)
                    event->acceptProposedAction();
                else
                    event->ignore();
                break;
            case 1:
                if(event->mimeData()->objectName().compare("RadarTrack") == 0)
                    event->acceptProposedAction();
                else
                    event->ignore();
                break;
            case 2:
                if(event->mimeData()->objectName().compare("FuseTrack") == 0)
                    event->acceptProposedAction();
                else
                    event->ignore();
                break;
            }
            return;
        }
    }
    event->ignore();
    QTableWidget::dragMoveEvent(event);
}

void MyTableWidget::dropEvent(QDropEvent *event)
{
    //不允许本控件内拖动
    if (event->source() == this)
    event->ignore();

    if(event->mimeData()->hasText())
    {
        QPoint pos = event->pos();
        QString strTrack = event->mimeData()->text();
        MoveToTable(pos, strTrack);
        event->acceptProposedAction();
        return;
    }

    event->ignore();
    QTableWidget::dropEvent(event);
}

void MyTableWidget::MoveToTable(QPoint pos, QString strTrack)
{
    QModelIndex index = indexAt(pos);
    if(index.isValid())
    {
        int iRow = index.row();
        int iColumn = index.column();
        switch (iColumn)
        {
        case 0:
        {
            QStringList strList;
            for (int i = 0; i < rowCount(); i++)
            {
                if(item(i, 0) != nullptr)
                {
                    strList.append(item(i, 0)->text());
                }
            }
            if (strList.contains(strTrack))
            {
                QMessageBox::critical(nullptr, "error",
                                      QString("FuseTrack:%1").arg(strTrack));
            }
            else
            {
                setItem(iRow, 0, new QTableWidgetItem(strTrack));
            }
        }
            break;
        case 1:
        {
            QStringList strList;
            for (int i = 0; i < rowCount(); i++)
            {
                if(item(i, 1) != nullptr)
                {
                    strList.append(item(i, 1)->text().split(strSeparator));
                }
            }
            if (strList.contains(strTrack))
            {
                QMessageBox::critical(nullptr, "error",
                                      QString("RadarTrack:%1").arg(strTrack));
            }
            else
            {
                if (item(iRow, 1) == nullptr)
                {
                    setItem(iRow, 1, new QTableWidgetItem(strTrack));
                }
                else
                {
                    QString strComboTrack = item(iRow, 1)->text() + strSeparator + strTrack;
                    setItem(iRow, 1, new QTableWidgetItem(strComboTrack));
                }
            }
        }
            break;
        case 2:
        {
            QStringList strList;
            for (int i = 0; i < rowCount(); i++)
            {
                if(item(i, 2) != nullptr)
                {
                    strList.append(item(i, 2)->text());
                }
            }
            if (strList.contains(strTrack))
            {
                QMessageBox::critical(nullptr, "error",
                                      QString("FuseTrack:%1").arg(strTrack));
            }
            else
            {
                setItem(iRow, 2, new QTableWidgetItem(strTrack));
            }
        }
            break;
        }
    }
}
