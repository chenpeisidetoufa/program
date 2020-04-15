/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_WindowClass
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textEdit_monitor;

    void setupUi(QDialog *WindowClass)
    {
        if (WindowClass->objectName().isEmpty())
            WindowClass->setObjectName(QStringLiteral("WindowClass"));
        WindowClass->setEnabled(true);
        WindowClass->resize(600, 400);
        gridLayout = new QGridLayout(WindowClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        textEdit_monitor = new QTextEdit(WindowClass);
        textEdit_monitor->setObjectName(QStringLiteral("textEdit_monitor"));
        textEdit_monitor->setEnabled(true);
        textEdit_monitor->setReadOnly(true);

        gridLayout->addWidget(textEdit_monitor, 0, 0, 1, 1);


        retranslateUi(WindowClass);

        QMetaObject::connectSlotsByName(WindowClass);
    } // setupUi

    void retranslateUi(QDialog *WindowClass)
    {
        WindowClass->setWindowTitle(QApplication::translate("WindowClass", "Window", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WindowClass: public Ui_WindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
