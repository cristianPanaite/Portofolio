/********************************************************************************
** Form generated from reading UI file 'qtsemnalslot.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSEMNALSLOT_H
#define UI_QTSEMNALSLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTSemnalSlotClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTSemnalSlotClass)
    {
        if (QTSemnalSlotClass->objectName().isEmpty())
            QTSemnalSlotClass->setObjectName(QStringLiteral("QTSemnalSlotClass"));
        QTSemnalSlotClass->resize(600, 400);
        menuBar = new QMenuBar(QTSemnalSlotClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QTSemnalSlotClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTSemnalSlotClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QTSemnalSlotClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QTSemnalSlotClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QTSemnalSlotClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTSemnalSlotClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTSemnalSlotClass->setStatusBar(statusBar);

        retranslateUi(QTSemnalSlotClass);

        QMetaObject::connectSlotsByName(QTSemnalSlotClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTSemnalSlotClass)
    {
        QTSemnalSlotClass->setWindowTitle(QApplication::translate("QTSemnalSlotClass", "QTSemnalSlot", 0));
    } // retranslateUi

};

namespace Ui {
    class QTSemnalSlotClass: public Ui_QTSemnalSlotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSEMNALSLOT_H
