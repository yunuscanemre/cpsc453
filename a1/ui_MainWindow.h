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
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
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
    QPushButton *openFileButton;
    QPushButton *openFileButton_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1019, 677);
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
        openFileButton = new QPushButton(centralwidget);
        openFileButton->setObjectName(QString::fromUtf8("openFileButton"));

        horizontalLayout_2->addWidget(openFileButton);

        openFileButton_2 = new QPushButton(centralwidget);
        openFileButton_2->setObjectName(QString::fromUtf8("openFileButton_2"));

        horizontalLayout_2->addWidget(openFileButton_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        originalImgBox->setTitle(QApplication::translate("MainWindow", "Original Image", 0, QApplication::UnicodeUTF8));
        modifiedImageBox->setTitle(QApplication::translate("MainWindow", "Modified Image", 0, QApplication::UnicodeUTF8));
        openFileButton->setText(QApplication::translate("MainWindow", "Open Image...", 0, QApplication::UnicodeUTF8));
        openFileButton_2->setText(QApplication::translate("MainWindow", "Save Modified...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
