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

    ui->amplitudeGraph->addGraph(ui->amplitudeGraph->xAxis, ui->amplitudeGraph->yAxis);
    ui->amplitudeGraph->graph(0)->setPen(QPen(QColor(40, 110, 255))); // Blue line.
    //ui->amplitudeGraph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white), 3));
    ui->amplitudeGraph->yAxis->setRange(-1.1, 1.1);

    ui->resultGraph->addGraph(ui->resultGraph->xAxis, ui->resultGraph->yAxis);
    ui->resultGraph->graph(0)->setPen(QPen(QColor(40, 110, 255))); // Blue line.
    ui->resultGraph->yAxis->setRange(-1.1, 1.1);

    ui->phaseGraph->addGraph(ui->phaseGraph->xAxis, ui->phaseGraph->yAxis);
    ui->phaseGraph->graph(0)->setPen(QPen(QColor(40, 110, 255))); // Blue line.
    ui->phaseGraph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white), 3));
    ui->phaseGraph->yAxis->setRange(-5, 5);

    on_comboBox_currentIndexChanged("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RedrawGraphs()
{
    Vizualizer vz(ui->sampleSizeText->text().toInt(), ui->equationText->text());
    Vizualizer::Method method;
    FourierTransform::FFTMode mode;
    if(ui->comboBox->currentText() == "Discrete")
    {
        method = Vizualizer::cDiscreteMethod;
    }
    else
    {
        method = Vizualizer::cFastMethod;
        if(ui->comboBox_2->currentText() == "In Time")
        {
            mode = FourierTransform::decimationInTime;
        }
        else
        {
            mode = FourierTransform::decimationInFrequency;
        }
    }
    vz.DrawSinCosExpression(ui->sourceGraph);
    vz.DrawForwardTransform(ui->amplitudeGraph, method, mode);
    vz.DrawPhaseGraph(ui->phaseGraph, method, mode);
    vz.DrawBackwardTransform(ui->resultGraph, method, mode);
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
    if(ui->comboBox->currentText() == "Discrete")
    {
        ui->comboBox_2->setEnabled(false);
    }
    else
    {
        ui->comboBox_2->setEnabled(true);
    }
    RedrawGraphs();
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    RedrawGraphs();
}
