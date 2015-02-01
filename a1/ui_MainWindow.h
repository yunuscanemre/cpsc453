/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QSpinBox *rotationEntry;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_7;
    QStatusBar *statusbar;
    QMenuBar *menuBar;
    QMenu *menuSelection;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1019, 677);
        actionOpenImage = new QAction(MainWindow);
        actionOpenImage->setObjectName(QStringLiteral("actionOpenImage"));
        actionSaveImage = new QAction(MainWindow);
        actionSaveImage->setObjectName(QStringLiteral("actionSaveImage"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        originalImgBox = new QGroupBox(centralwidget);
        originalImgBox->setObjectName(QStringLiteral("originalImgBox"));
        verticalLayout = new QVBoxLayout(originalImgBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        origImgContainerWidget = new QWidget(originalImgBox);
        origImgContainerWidget->setObjectName(QStringLiteral("origImgContainerWidget"));

        verticalLayout->addWidget(origImgContainerWidget);


        horizontalLayout->addWidget(originalImgBox);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        modifiedImageBox = new QGroupBox(centralwidget);
        modifiedImageBox->setObjectName(QStringLiteral("modifiedImageBox"));
        verticalLayout_2 = new QVBoxLayout(modifiedImageBox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        modImgContainerWidget = new QWidget(modifiedImageBox);
        modImgContainerWidget->setObjectName(QStringLiteral("modImgContainerWidget"));

        verticalLayout_2->addWidget(modImgContainerWidget);


        horizontalLayout->addWidget(modifiedImageBox);


        verticalLayout_3->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        brightnessEntry = new QDoubleSpinBox(centralwidget);
        brightnessEntry->setObjectName(QStringLiteral("brightnessEntry"));
        brightnessEntry->setKeyboardTracking(false);
        brightnessEntry->setDecimals(1);
        brightnessEntry->setMinimum(0);
        brightnessEntry->setMaximum(50);
        brightnessEntry->setSingleStep(0.1);
        brightnessEntry->setValue(1);

        gridLayout->addWidget(brightnessEntry, 1, 2, 1, 1);

        dissolveSelect = new QPushButton(centralwidget);
        dissolveSelect->setObjectName(QStringLiteral("dissolveSelect"));

        gridLayout->addWidget(dissolveSelect, 6, 1, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        dissolveEntry = new QDoubleSpinBox(centralwidget);
        dissolveEntry->setObjectName(QStringLiteral("dissolveEntry"));
        dissolveEntry->setEnabled(false);
        dissolveEntry->setKeyboardTracking(false);
        dissolveEntry->setDecimals(1);
        dissolveEntry->setMaximum(1);
        dissolveEntry->setSingleStep(0.1);

        gridLayout->addWidget(dissolveEntry, 6, 2, 1, 1);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 5, 1, 1, 1);

        contrastEntry = new QDoubleSpinBox(centralwidget);
        contrastEntry->setObjectName(QStringLiteral("contrastEntry"));
        contrastEntry->setKeyboardTracking(false);
        contrastEntry->setDecimals(1);
        contrastEntry->setMinimum(-10);
        contrastEntry->setMaximum(50);
        contrastEntry->setSingleStep(0.1);
        contrastEntry->setValue(1);

        gridLayout->addWidget(contrastEntry, 5, 2, 1, 1);

        saturationEntry = new QDoubleSpinBox(centralwidget);
        saturationEntry->setObjectName(QStringLiteral("saturationEntry"));
        saturationEntry->setKeyboardTracking(false);
        saturationEntry->setDecimals(1);
        saturationEntry->setMinimum(-10);
        saturationEntry->setMaximum(50);
        saturationEntry->setSingleStep(0.1);
        saturationEntry->setValue(1);

        gridLayout->addWidget(saturationEntry, 2, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 5, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        quantizationEntry = new QSpinBox(centralwidget);
        quantizationEntry->setObjectName(QStringLiteral("quantizationEntry"));
        quantizationEntry->setKeyboardTracking(false);
        quantizationEntry->setMinimum(2);
        quantizationEntry->setMaximum(256);
        quantizationEntry->setValue(256);

        gridLayout->addWidget(quantizationEntry, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        scaleEntry = new QSpinBox(centralwidget);
        scaleEntry->setObjectName(QStringLiteral("scaleEntry"));
        scaleEntry->setKeyboardTracking(false);
        scaleEntry->setMinimum(1);
        scaleEntry->setMaximum(5);
        scaleEntry->setValue(1);

        gridLayout->addWidget(scaleEntry, 3, 2, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 3, 0, 1, 1);

        rotationEntry = new QSpinBox(centralwidget);
        rotationEntry->setObjectName(QStringLiteral("rotationEntry"));
        rotationEntry->setKeyboardTracking(false);
        rotationEntry->setMaximum(360);
        rotationEntry->setSingleStep(1);

        gridLayout->addWidget(rotationEntry, 4, 2, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 4, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1019, 27));
        menuSelection = new QMenu(menuBar);
        menuSelection->setObjectName(QStringLiteral("menuSelection"));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CPSC453 - A1", 0));
        actionOpenImage->setText(QApplication::translate("MainWindow", "Open BMP Image...", 0));
        actionSaveImage->setText(QApplication::translate("MainWindow", "Save BMP Image...", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        originalImgBox->setTitle(QApplication::translate("MainWindow", "Original Image", 0));
        modifiedImageBox->setTitle(QApplication::translate("MainWindow", "Modified Image", 0));
        label_2->setText(QApplication::translate("MainWindow", "Brigtness Scale", 0));
        dissolveSelect->setText(QApplication::translate("MainWindow", "*Dissolve Image...", 0));
        label_3->setText(QApplication::translate("MainWindow", "Saturation", 0));
        label_4->setText(QApplication::translate("MainWindow", "*Contrast", 0));
        label->setText(QApplication::translate("MainWindow", "Quantization Level", 0));
        label_5->setText(QApplication::translate("MainWindow", "Scale", 0));
        label_6->setText(QApplication::translate("MainWindow", "Rotate", 0));
        menuSelection->setTitle(QApplication::translate("MainWindow", "Menu", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
