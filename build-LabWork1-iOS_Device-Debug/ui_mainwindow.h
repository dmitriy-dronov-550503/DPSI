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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QCustomPlot *sourceGraph;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *equationText;
    QLabel *label_2;
    QLineEdit *sampleSizeText;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QCustomPlot *phaseGraph;
    QCustomPlot *resultGraph;
    QCustomPlot *amplitudeGraph;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(652, 449);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        sourceGraph = new QCustomPlot(centralWidget);
        sourceGraph->setObjectName(QStringLiteral("sourceGraph"));

        gridLayout->addWidget(sourceGraph, 1, 0, 1, 1);

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

        comboBox_2 = new QComboBox(widget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        horizontalLayout->setStretch(1, 50);
        horizontalLayout->setStretch(3, 7);
        horizontalLayout->setStretch(5, 20);

        gridLayout->addWidget(widget, 0, 0, 1, 2);

        phaseGraph = new QCustomPlot(centralWidget);
        phaseGraph->setObjectName(QStringLiteral("phaseGraph"));

        gridLayout->addWidget(phaseGraph, 2, 1, 1, 1);

        resultGraph = new QCustomPlot(centralWidget);
        resultGraph->setObjectName(QStringLiteral("resultGraph"));

        gridLayout->addWidget(resultGraph, 2, 0, 1, 1);

        amplitudeGraph = new QCustomPlot(centralWidget);
        amplitudeGraph->setObjectName(QStringLiteral("amplitudeGraph"));

        gridLayout->addWidget(amplitudeGraph, 1, 1, 1, 1);

        gridLayout->setRowStretch(1, 40);
        gridLayout->setRowStretch(2, 40);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Fourier Transform", nullptr));
        label->setText(QApplication::translate("MainWindow", "y =", nullptr));
        equationText->setText(QApplication::translate("MainWindow", "sin(2*x)+cos(7*x)", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "N = ", nullptr));
        sampleSizeText->setText(QApplication::translate("MainWindow", "64", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Discrete", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Fast", nullptr));

        comboBox_2->setItemText(0, QApplication::translate("MainWindow", "In Frequency", nullptr));
        comboBox_2->setItemText(1, QApplication::translate("MainWindow", "In Time", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
