#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Vizualizer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->source1Graph->addGraph(ui->source1Graph->xAxis, ui->source1Graph->yAxis);
    ui->source1Graph->addGraph(ui->source1Graph->xAxis, ui->source1Graph->yAxis);
    ui->source1Graph->graph(0)->setPen(QPen(QColor(40, 110, 255), 1)); // Blue line.
    ui->source1Graph->plotLayout()->addElement(1, 0, new QCPTextElement(ui->source1Graph, "y = " + ui->equation1Text->text(), QFont("sans", 12)));
    ui->source1Graph->yAxis->setRange(-1.1, 1.1);

    ui->source2Graph->addGraph(ui->source2Graph->xAxis, ui->source2Graph->yAxis);
    ui->source2Graph->addGraph(ui->source2Graph->xAxis, ui->source2Graph->yAxis);
    ui->source2Graph->graph(0)->setPen(QPen(QColor(240, 50, 40), 1)); // Red line.
    ui->source2Graph->plotLayout()->addElement(1, 0, new QCPTextElement(ui->source2Graph, "y = " + ui->equation1Text->text(), QFont("sans", 12)));
    ui->source2Graph->yAxis->setRange(-1.1, 1.1);

    ui->convolutionGraph->addGraph(ui->convolutionGraph->xAxis, ui->convolutionGraph->yAxis);
    ui->convolutionGraph->graph(0)->setPen(QPen(QColor(230, 30, 230))); // Violet line.
    ui->convolutionGraph->plotLayout()->addElement(1, 0, new QCPTextElement(ui->convolutionGraph, "Convolution", QFont("sans", 12)));
    //ui->convolutionGraph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white), 3));
    ui->convolutionGraph->yAxis->setRange(-1.1, 1.1);

    ui->correlationGraph->addGraph(ui->correlationGraph->xAxis, ui->correlationGraph->yAxis);
    ui->correlationGraph->graph(0)->setPen(QPen(QColor(230, 30, 230))); // Violet line.
    ui->correlationGraph->plotLayout()->addElement(1, 0, new QCPTextElement(ui->correlationGraph, "Correlation", QFont("sans", 12)));
    //ui->correlationGraph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white), 3));
    ui->correlationGraph->yAxis->setRange(-5, 5);

    on_comboBox_currentIndexChanged("");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::RedrawGraphs()
{
    Vizualizer vz(ui->sampleSizeText->text().toInt(), ui->equation1Text->text(), ui->equation2Text->text());
    Vizualizer::Method method;
    QCPTextElement* el = (QCPTextElement*)ui->source1Graph->plotLayout()->element(1, 0);
    el->setText("y = " + ui->equation1Text->text());
    el = (QCPTextElement*)ui->source2Graph->plotLayout()->element(1, 0);
    el->setText("y = " + ui->equation2Text->text());

    if(ui->comboBox->currentText() == "Generic")
    {
        method = Vizualizer::cGenericMethod;
    }
    else
    {
        method = Vizualizer::cFFTMethod;
    }

    vz.DrawSinCosExpression(ui->source1Graph, ui->source2Graph);
    vz.DrawConvolutionGraph(ui->convolutionGraph, method);
    vz.DrawCorrelationGraph(ui->correlationGraph, method);
}

void MainWindow::on_equation1Text_returnPressed()
{
    RedrawGraphs();
}

void MainWindow::on_equation2Text_returnPressed()
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

