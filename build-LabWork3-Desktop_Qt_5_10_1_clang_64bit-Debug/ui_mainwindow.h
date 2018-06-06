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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QCustomPlot *resultGraph;
    QCustomPlot *walshGraph;
    QCustomPlot *sourceGraph;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *equationText;
    QCheckBox *checkBox;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *sampleSizeText;
    QComboBox *comboBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(652, 574);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        resultGraph = new QCustomPlot(centralWidget);
        resultGraph->setObjectName(QStringLiteral("resultGraph"));

        gridLayout->addWidget(resultGraph, 4, 0, 1, 1);

        walshGraph = new QCustomPlot(centralWidget);
        walshGraph->setObjectName(QStringLiteral("walshGraph"));

        gridLayout->addWidget(walshGraph, 3, 0, 1, 1);

        sourceGraph = new QCustomPlot(centralWidget);
        sourceGraph->setObjectName(QStringLiteral("sourceGraph"));

        gridLayout->addWidget(sourceGraph, 2, 0, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        equationText = new QLineEdit(widget);
        equationText->setObjectName(QStringLiteral("equationText"));

        horizontalLayout->addWidget(equationText);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setChecked(true);
        checkBox->setTristate(false);

        horizontalLayout->addWidget(checkBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        sampleSizeText = new QLineEdit(widget);
        sampleSizeText->setObjectName(QStringLiteral("sampleSizeText"));

        horizontalLayout->addWidget(sampleSizeText);

        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalLayout->setStretch(1, 50);
        horizontalLayout->setStretch(5, 7);

        gridLayout->addWidget(widget, 1, 0, 1, 1);

        gridLayout->setRowStretch(2, 10);
        gridLayout->setRowStretch(3, 10);
        gridLayout->setRowStretch(4, 10);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Fourier Transform", nullptr));
        label->setText(QApplication::translate("MainWindow", "y =", nullptr));
        equationText->setText(QApplication::translate("MainWindow", "sin(2*x)+cos(7*x)", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Hadamard -> Walsh", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "N = ", nullptr));
        sampleSizeText->setText(QApplication::translate("MainWindow", "64", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Discrete", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Fast", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
