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
    QCustomPlot *source1Graph;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *equation1Text;
    QLabel *label_3;
    QLineEdit *equation2Text;
    QLabel *label_2;
    QLineEdit *sampleSizeText;
    QComboBox *comboBox;
    QCustomPlot *correlationGraph;
    QCustomPlot *source2Graph;
    QCustomPlot *convolutionGraph;

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
        source1Graph = new QCustomPlot(centralWidget);
        source1Graph->setObjectName(QStringLiteral("source1Graph"));

        gridLayout->addWidget(source1Graph, 1, 0, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("color: rgb(40, 110, 255);"));

        horizontalLayout->addWidget(label);

        equation1Text = new QLineEdit(widget);
        equation1Text->setObjectName(QStringLiteral("equation1Text"));

        horizontalLayout->addWidget(equation1Text);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral("color: rgb(240, 50, 40);"));

        horizontalLayout->addWidget(label_3);

        equation2Text = new QLineEdit(widget);
        equation2Text->setObjectName(QStringLiteral("equation2Text"));

        horizontalLayout->addWidget(equation2Text);

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

        horizontalLayout->setStretch(1, 12);
        horizontalLayout->setStretch(3, 12);
        horizontalLayout->setStretch(5, 10);

        gridLayout->addWidget(widget, 0, 0, 1, 2);

        correlationGraph = new QCustomPlot(centralWidget);
        correlationGraph->setObjectName(QStringLiteral("correlationGraph"));

        gridLayout->addWidget(correlationGraph, 2, 1, 1, 1);

        source2Graph = new QCustomPlot(centralWidget);
        source2Graph->setObjectName(QStringLiteral("source2Graph"));

        gridLayout->addWidget(source2Graph, 2, 0, 1, 1);

        convolutionGraph = new QCustomPlot(centralWidget);
        convolutionGraph->setObjectName(QStringLiteral("convolutionGraph"));

        gridLayout->addWidget(convolutionGraph, 1, 1, 1, 1);

        gridLayout->setRowStretch(1, 40);
        gridLayout->setRowStretch(2, 40);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Fourier Transform", nullptr));
        label->setText(QApplication::translate("MainWindow", "y1 =", nullptr));
        equation1Text->setText(QApplication::translate("MainWindow", "sin(2*x)", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "y2=", nullptr));
        equation2Text->setText(QApplication::translate("MainWindow", "cos(7*x)", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "N = ", nullptr));
        sampleSizeText->setText(QApplication::translate("MainWindow", "64", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "FFT", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Generic", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
