/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenImage;
    QAction *actionSaveImage;
    QAction *actionExit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QGroupBox *originalImgBox;
    QVBoxLayout *verticalLayout;
    QWidget *origImgContainerWidget;
    QSpacerItem *horizontalSpacer;
    QGroupBox *modifiedImageBox;
    QVBoxLayout *verticalLayout_2;
    QWidget *modImgContainerWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpinBox *quantizationEntry;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuSelection;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1019, 677);
        actionOpenImage = new QAction(MainWindow);
        actionOpenImage->setObjectName(QString::fromUtf8("actionOpenImage"));
        actionSaveImage = new QAction(MainWindow);
        actionSaveImage->setObjectName(QString::fromUtf8("actionSaveImage"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        originalImgBox = new QGroupBox(centralwidget);
        originalImgBox->setObjectName(QString::fromUtf8("originalImgBox"));
        verticalLayout = new QVBoxLayout(originalImgBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        origImgContainerWidget = new QWidget(originalImgBox);
        origImgContainerWidget->setObjectName(QString::fromUtf8("origImgContainerWidget"));

        verticalLayout->addWidget(origImgContainerWidget);


        horizontalLayout->addWidget(originalImgBox);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        modifiedImageBox = new QGroupBox(centralwidget);
        modifiedImageBox->setObjectName(QString::fromUtf8("modifiedImageBox"));
        verticalLayout_2 = new QVBoxLayout(modifiedImageBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        modImgContainerWidget = new QWidget(modifiedImageBox);
        modImgContainerWidget->setObjectName(QString::fromUtf8("modImgContainerWidget"));

        verticalLayout_2->addWidget(modImgContainerWidget);


        horizontalLayout->addWidget(modifiedImageBox);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        quantizationEntry = new QSpinBox(centralwidget);
        quantizationEntry->setObjectName(QString::fromUtf8("quantizationEntry"));
        quantizationEntry->setKeyboardTracking(false);
        quantizationEntry->setMinimum(2);
        quantizationEntry->setMaximum(256);
        quantizationEntry->setValue(256);

        horizontalLayout_2->addWidget(quantizationEntry);


        verticalLayout_3->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1019, 27));
        menuSelection = new QMenu(menuBar);
        menuSelection->setObjectName(QString::fromUtf8("menuSelection"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuSelection->menuAction());
        menuSelection->addAction(actionOpenImage);
        menuSelection->addAction(actionSaveImage);
        menuSelection->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionOpenImage->setText(QApplication::translate("MainWindow", "Open BMP Image...", 0, QApplication::UnicodeUTF8));
        actionSaveImage->setText(QApplication::translate("MainWindow", "Save BMP Image...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        originalImgBox->setTitle(QApplication::translate("MainWindow", "Original Image", 0, QApplication::UnicodeUTF8));
        modifiedImageBox->setTitle(QApplication::translate("MainWindow", "Modified Image", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Quantization Level", 0, QApplication::UnicodeUTF8));
        menuSelection->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
