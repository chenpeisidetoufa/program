/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QWidget *widget_Save;
    QGridLayout *gridLayout_3;
    QLineEdit *lineEdit_Name;
    QPushButton *pushButton_Save;
    QWidget *widget_Read;
    QGridLayout *gridLayout_2;
    QListWidget *listWidget_Read;
    QPushButton *pushButton_Read;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(578, 478);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget_Save = new QWidget(centralWidget);
        widget_Save->setObjectName(QStringLiteral("widget_Save"));
        gridLayout_3 = new QGridLayout(widget_Save);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        lineEdit_Name = new QLineEdit(widget_Save);
        lineEdit_Name->setObjectName(QStringLiteral("lineEdit_Name"));

        gridLayout_3->addWidget(lineEdit_Name, 0, 0, 1, 1);

        pushButton_Save = new QPushButton(widget_Save);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));

        gridLayout_3->addWidget(pushButton_Save, 1, 0, 1, 1);


        verticalLayout->addWidget(widget_Save);

        widget_Read = new QWidget(centralWidget);
        widget_Read->setObjectName(QStringLiteral("widget_Read"));
        gridLayout_2 = new QGridLayout(widget_Read);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        listWidget_Read = new QListWidget(widget_Read);
        listWidget_Read->setObjectName(QStringLiteral("listWidget_Read"));

        gridLayout_2->addWidget(listWidget_Read, 0, 0, 1, 1);

        pushButton_Read = new QPushButton(widget_Read);
        pushButton_Read->setObjectName(QStringLiteral("pushButton_Read"));

        gridLayout_2->addWidget(pushButton_Read, 1, 0, 1, 1);


        verticalLayout->addWidget(widget_Read);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 578, 26));
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
        pushButton_Save->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244", Q_NULLPTR));
        pushButton_Read->setText(QApplication::translate("MainWindow", "\347\241\256\350\256\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
