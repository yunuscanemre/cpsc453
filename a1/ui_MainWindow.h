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
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
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
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QDoubleSpinBox *brightnessEntry;
    QPushButton *dissolveSelect;
    QLabel *label_3;
    QDoubleSpinBox *dissolveEntry;
    QLabel *label_4;
    QDoubleSpinBox *contrastEntry;
    QDoubleSpinBox *saturationEntry;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label;
    QSpinBox *quantizationEntry;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *scaleEntry;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_6;
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

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        brightnessEntry = new QDoubleSpinBox(centralwidget);
        brightnessEntry->setObjectName(QString::fromUtf8("brightnessEntry"));
        brightnessEntry->setKeyboardTracking(false);
        brightnessEntry->setDecimals(1);
        brightnessEntry->setMinimum(0);
        brightnessEntry->setMaximum(50);
        brightnessEntry->setSingleStep(0.1);
        brightnessEntry->setValue(1);

        gridLayout->addWidget(brightnessEntry, 1, 2, 1, 1);

        dissolveSelect = new QPushButton(centralwidget);
        dissolveSelect->setObjectName(QString::fromUtf8("dissolveSelect"));

        gridLayout->addWidget(dissolveSelect, 5, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        dissolveEntry = new QDoubleSpinBox(centralwidget);
        dissolveEntry->setObjectName(QString::fromUtf8("dissolveEntry"));
        dissolveEntry->setEnabled(false);
        dissolveEntry->setKeyboardTracking(false);
        dissolveEntry->setDecimals(1);
        dissolveEntry->setMaximum(1);
        dissolveEntry->setSingleStep(0.1);

        gridLayout->addWidget(dissolveEntry, 5, 2, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 1, 1, 1);

        contrastEntry = new QDoubleSpinBox(centralwidget);
        contrastEntry->setObjectName(QString::fromUtf8("contrastEntry"));
        contrastEntry->setKeyboardTracking(false);
        contrastEntry->setDecimals(1);
        contrastEntry->setMinimum(-10);
        contrastEntry->setMaximum(50);
        contrastEntry->setSingleStep(0.1);
        contrastEntry->setValue(1);

        gridLayout->addWidget(contrastEntry, 4, 2, 1, 1);

        saturationEntry = new QDoubleSpinBox(centralwidget);
        saturationEntry->setObjectName(QString::fromUtf8("saturationEntry"));
        saturationEntry->setKeyboardTracking(false);
        saturationEntry->setDecimals(1);
        saturationEntry->setMinimum(-10);
        saturationEntry->setMaximum(50);
        saturationEntry->setSingleStep(0.1);
        saturationEntry->setValue(1);

        gridLayout->addWidget(saturationEntry, 2, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 4, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        quantizationEntry = new QSpinBox(centralwidget);
        quantizationEntry->setObjectName(QString::fromUtf8("quantizationEntry"));
        quantizationEntry->setKeyboardTracking(false);
        quantizationEntry->setMinimum(2);
        quantizationEntry->setMaximum(256);
        quantizationEntry->setValue(256);

        gridLayout->addWidget(quantizationEntry, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        scaleEntry = new QSpinBox(centralwidget);
        scaleEntry->setObjectName(QString::fromUtf8("scaleEntry"));
        scaleEntry->setKeyboardTracking(false);
        scaleEntry->setMinimum(1);
        scaleEntry->setMaximum(5);
        scaleEntry->setValue(1);

        gridLayout->addWidget(scaleEntry, 3, 2, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 3, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CPSC453 - A1", 0, QApplication::UnicodeUTF8));
        actionOpenImage->setText(QApplication::translate("MainWindow", "Open BMP Image...", 0, QApplication::UnicodeUTF8));
        actionSaveImage->setText(QApplication::translate("MainWindow", "Save BMP Image...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        originalImgBox->setTitle(QApplication::translate("MainWindow", "Original Image", 0, QApplication::UnicodeUTF8));
        modifiedImageBox->setTitle(QApplication::translate("MainWindow", "Modified Image", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Brigtness Scale", 0, QApplication::UnicodeUTF8));
        dissolveSelect->setText(QApplication::translate("MainWindow", "*Dissolve Image...", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Saturation", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "*Contrast", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Quantization Level", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Scale", 0, QApplication::UnicodeUTF8));
        menuSelection->setTitle(QApplication::translate("MainWindow", "Menu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
