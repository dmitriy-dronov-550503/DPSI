#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Vizualizer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sourceGraph->addGraph(ui->sourceGraph->xAxis, ui->sourceGraph->yAxis);
    ui->sourceGraph->graph(0)->setPen(QPen(QColor(40, 110, 255))); // Blue line.
    ui->sourceGraph->yAxis->setRange(-1.1, 1.1);

    ui->walshGraph->addGraph(ui->walshGraph->xAxis, ui->walshGraph->yAxis);
    ui->walshGraph->graph(0)->setPen(QPen(QColor(40, 110, 255))); // Blue line.
    //ui->walshGraph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white), 3));
    ui->walshGraph->yAxis->setRange(-1.1, 1.1);

    ui->resultGraph->addGraph(ui->resultGraph->xAxis, ui->resultGraph->yAxis);
    ui->resultGraph->graph(0)->setPen(QPen(QColor(40, 110, 255))); // Blue line.
    ui->resultGraph->yAxis->setRange(-1.1, 1.1);

    on_comboBox_currentIndexChanged("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RedrawGraphs()
{
    int sampleSize = ui->sampleSizeText->text().toInt();
    double l2ss = log2((double)sampleSize);
    if(!(l2ss == (int)l2ss) || (sampleSize < 2))
    {
        QMessageBox msgBox;
        msgBox.setText("Please provide the N to be the power of 2.");
        msgBox.exec();
        return;
    }
    Vizualizer vz(ui->sampleSizeText->text().toInt(), ui->equationText->text(), ui->checkBox->isChecked());
    Vizualizer::Method method;
    if(ui->comboBox->currentText() == "Discrete")
    {
        method = Vizualizer::cDiscreteMethod;
    }
    else
    {
        method = Vizualizer::cFastMethod;
    }
    vz.DrawSinCosExpression(ui->sourceGraph);
    vz.DrawForwardTransform(ui->walshGraph, method);
    vz.DrawBackwardTransform(ui->resultGraph, method);
}

void MainWindow::on_equationText_returnPressed()
{
    RedrawGraphs();

}

void MainWindow::on_sampleSizeText_returnPressed()
{
    RedrawGraphs();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    RedrawGraphs();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    RedrawGraphs();
}
