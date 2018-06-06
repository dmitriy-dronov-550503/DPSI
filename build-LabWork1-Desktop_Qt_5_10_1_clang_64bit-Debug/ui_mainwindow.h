/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tabFIR;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *equationText;
    QSlider *horizontalSlider;
    QLineEdit *frequencyText;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *sampleSizeText;
    QCheckBox *checkBox;
    QWidget *tabIIR;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *equationText_2;
    QSlider *horizontalSlider_2;
    QLineEdit *frequencyText_2;
    QLabel *label_5;
    QLineEdit *bwLineEdit;
    QLabel *label_4;
    QLineEdit *sampleSizeText_2;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QCustomPlot *frequencyGraph;
    QCustomPlot *sourceGraph;
    QCustomPlot *FIRGraph;
    QCustomPlot *impulseGraph;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(652, 449);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(10, 10, 10, 10);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabFIR = new QWidget();
        tabFIR->setObjectName(QStringLiteral("tabFIR"));
        verticalLayout = new QVBoxLayout(tabFIR);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(tabFIR);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("color: rgb(40, 110, 255);"));

        horizontalLayout->addWidget(label);

        equationText = new QLineEdit(widget);
        equationText->setObjectName(QStringLiteral("equationText"));

        horizontalLayout->addWidget(equationText);

        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalSlider->sizePolicy().hasHeightForWidth());
        horizontalSlider->setSizePolicy(sizePolicy);
        horizontalSlider->setMinimum(1);
        horizontalSlider->setValue(20);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBothSides);

        horizontalLayout->addWidget(horizontalSlider);

        frequencyText = new QLineEdit(widget);
        frequencyText->setObjectName(QStringLiteral("frequencyText"));
        frequencyText->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout->addWidget(frequencyText);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        sampleSizeText = new QLineEdit(widget);
        sampleSizeText->setObjectName(QStringLiteral("sampleSizeText"));
        sampleSizeText->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout->addWidget(sampleSizeText);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);

        horizontalLayout->addWidget(checkBox);

        horizontalLayout->setStretch(1, 15);
        horizontalLayout->setStretch(2, 12);
        horizontalLayout->setStretch(3, 3);
        horizontalLayout->setStretch(6, 3);

        verticalLayout->addWidget(widget);

        tabWidget->addTab(tabFIR, QString());
        tabIIR = new QWidget();
        tabIIR->setObjectName(QStringLiteral("tabIIR"));
        verticalLayout_3 = new QVBoxLayout(tabIIR);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(tabIIR);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("color: rgb(40, 110, 255);"));

        horizontalLayout_2->addWidget(label_3);

        equationText_2 = new QLineEdit(widget_3);
        equationText_2->setObjectName(QStringLiteral("equationText_2"));
        equationText_2->setDragEnabled(false);

        horizontalLayout_2->addWidget(equationText_2);

        horizontalSlider_2 = new QSlider(widget_3);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        sizePolicy.setHeightForWidth(horizontalSlider_2->sizePolicy().hasHeightForWidth());
        horizontalSlider_2->setSizePolicy(sizePolicy);
        horizontalSlider_2->setMinimum(1);
        horizontalSlider_2->setValue(20);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_2->setTickPosition(QSlider::TicksBothSides);

        horizontalLayout_2->addWidget(horizontalSlider_2);

        frequencyText_2 = new QLineEdit(widget_3);
        frequencyText_2->setObjectName(QStringLiteral("frequencyText_2"));
        frequencyText_2->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout_2->addWidget(frequencyText_2);

        label_5 = new QLabel(widget_3);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        bwLineEdit = new QLineEdit(widget_3);
        bwLineEdit->setObjectName(QStringLiteral("bwLineEdit"));
        bwLineEdit->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout_2->addWidget(bwLineEdit);

        label_4 = new QLabel(widget_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        sampleSizeText_2 = new QLineEdit(widget_3);
        sampleSizeText_2->setObjectName(QStringLiteral("sampleSizeText_2"));
        sampleSizeText_2->setInputMethodHints(Qt::ImhDigitsOnly);

        horizontalLayout_2->addWidget(sampleSizeText_2);

        horizontalLayout_2->setStretch(1, 15);
        horizontalLayout_2->setStretch(2, 12);
        horizontalLayout_2->setStretch(3, 3);
        horizontalLayout_2->setStretch(5, 3);
        horizontalLayout_2->setStretch(7, 3);

        verticalLayout_3->addWidget(widget_3);

        tabWidget->addTab(tabIIR, QString());

        verticalLayout_2->addWidget(tabWidget);

        widget_2 = new QWidget(centralWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frequencyGraph = new QCustomPlot(widget_2);
        frequencyGraph->setObjectName(QStringLiteral("frequencyGraph"));

        gridLayout_2->addWidget(frequencyGraph, 1, 0, 1, 1);

        sourceGraph = new QCustomPlot(widget_2);
        sourceGraph->setObjectName(QStringLiteral("sourceGraph"));

        gridLayout_2->addWidget(sourceGraph, 0, 0, 1, 1);

        FIRGraph = new QCustomPlot(widget_2);
        FIRGraph->setObjectName(QStringLiteral("FIRGraph"));

        gridLayout_2->addWidget(FIRGraph, 0, 1, 1, 1);

        impulseGraph = new QCustomPlot(widget_2);
        impulseGraph->setObjectName(QStringLiteral("impulseGraph"));

        gridLayout_2->addWidget(impulseGraph, 1, 1, 1, 1);


        verticalLayout_2->addWidget(widget_2);

        verticalLayout_2->setStretch(1, 50);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Fourier Transform", nullptr));
        label->setText(QApplication::translate("MainWindow", "y =", nullptr));
        equationText->setText(QApplication::translate("MainWindow", "sin(3*x)+cos(10*x)+sin(30*x)+sin(x*R1)+cos(x*R2)+sin(x*R3)", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "N = ", nullptr));
        sampleSizeText->setText(QApplication::translate("MainWindow", "256", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Hamming", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabFIR), QApplication::translate("MainWindow", "\320\232\320\230\320\245 \320\244\320\235\320\247", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "y =", nullptr));
        equationText_2->setText(QApplication::translate("MainWindow", "sin(30*x)+sin(80*x)", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "BW=", nullptr));
        bwLineEdit->setText(QApplication::translate("MainWindow", "10", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "N = ", nullptr));
        sampleSizeText_2->setText(QApplication::translate("MainWindow", "256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabIIR), QApplication::translate("MainWindow", "\320\221\320\230\320\245 \320\277\320\276\320\273\320\276\321\201\320\276\320\262\320\276\320\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
