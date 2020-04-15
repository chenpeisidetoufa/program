/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <MyTableView.h>
#include <MyTableWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_RealTrack;
    QGridLayout *gridLayout;
    MyTableView *tableView_RealTrack;
    QGroupBox *groupBox_RadarTrack;
    QGridLayout *gridLayout_3;
    MyTableView *tableView_RadarTrack;
    QGroupBox *groupBox_FuseTrack;
    QGridLayout *gridLayout_2;
    MyTableView *tableView_FuseTrack;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    MyTableWidget *tableWidget_Correlation;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(909, 666);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_5 = new QGridLayout(centralWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_RealTrack = new QGroupBox(centralWidget);
        groupBox_RealTrack->setObjectName(QStringLiteral("groupBox_RealTrack"));
        gridLayout = new QGridLayout(groupBox_RealTrack);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableView_RealTrack = new MyTableView(groupBox_RealTrack);
        tableView_RealTrack->setObjectName(QStringLiteral("tableView_RealTrack"));

        gridLayout->addWidget(tableView_RealTrack, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_RealTrack);

        groupBox_RadarTrack = new QGroupBox(centralWidget);
        groupBox_RadarTrack->setObjectName(QStringLiteral("groupBox_RadarTrack"));
        gridLayout_3 = new QGridLayout(groupBox_RadarTrack);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableView_RadarTrack = new MyTableView(groupBox_RadarTrack);
        tableView_RadarTrack->setObjectName(QStringLiteral("tableView_RadarTrack"));

        gridLayout_3->addWidget(tableView_RadarTrack, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_RadarTrack);

        groupBox_FuseTrack = new QGroupBox(centralWidget);
        groupBox_FuseTrack->setObjectName(QStringLiteral("groupBox_FuseTrack"));
        gridLayout_2 = new QGridLayout(groupBox_FuseTrack);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tableView_FuseTrack = new MyTableView(groupBox_FuseTrack);
        tableView_FuseTrack->setObjectName(QStringLiteral("tableView_FuseTrack"));

        gridLayout_2->addWidget(tableView_FuseTrack, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_FuseTrack);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tableWidget_Correlation = new MyTableWidget(groupBox_4);
        tableWidget_Correlation->setObjectName(QStringLiteral("tableWidget_Correlation"));

        gridLayout_4->addWidget(tableWidget_Correlation, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 909, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox_RealTrack->setTitle(QApplication::translate("MainWindow", "\347\234\237\345\200\274GPS\350\210\252\350\277\271", Q_NULLPTR));
        groupBox_RadarTrack->setTitle(QApplication::translate("MainWindow", "\351\233\267\350\276\276\350\210\252\350\277\271", Q_NULLPTR));
        groupBox_FuseTrack->setTitle(QApplication::translate("MainWindow", "\350\236\215\345\220\210\350\210\252\350\277\271", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "\350\210\252\350\277\271\347\233\270\345\205\263\350\241\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
