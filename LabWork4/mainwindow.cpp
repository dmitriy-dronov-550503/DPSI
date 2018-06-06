#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Vizualizer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sourceGraph->addGraph(ui->sourceGraph->xAxis, ui->sourceGraph->yAxis);
    ui->sourceGraph->addGraph(ui->sourceGraph->xAxis, ui->sourceGraph->yAxis);
    ui->sourceGraph->graph(0)->setPen(QPen(QColor(40, 110, 255))); // Blue line.
    ui->sourceGraph->plotLayout()->addElement(1, 0, new QCPTextElement(ui->sourceGraph, "y = " + ui->equationText->text(), QFont("sans", 12)));
    ui->sourceGraph->yAxis->setRange(-1.1, 1.1);

    ui->frequencyGraph->addGraph(ui->frequencyGraph->xAxis, ui->frequencyGraph->yAxis);
    ui->frequencyGraph->graph(0)->setPen(QPen(QColor(240, 50, 40))); // Red line.
    ui->frequencyGraph->plotLayout()->addElement(1, 0, new QCPTextElement(ui->frequencyGraph, "Frequency response", QFont("sans", 12)));
    ui->frequencyGraph->yAxis->setRange(-1.1, 1.1);
    ui->frequencyGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->FIRGraph->addGraph(ui->FIRGraph->xAxis, ui->FIRGraph->yAxis);
    ui->FIRGraph->graph(0)->setPen(QPen(QColor(230, 30, 230))); // Violet line.
    ui->FIRGraph->plotLayout()->addElement(1, 0, new QCPTextElement(ui->FIRGraph, "Filtered", QFont("sans", 12)));
    //ui->kixGraph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white), 3));
    ui->FIRGraph->yAxis->setRange(-1.1, 1.1);

    ui->impulseGraph->addGraph(ui->impulseGraph->xAxis, ui->impulseGraph->yAxis);
    ui->impulseGraph->graph(0)->setPen(QPen(QColor(230, 30, 230))); // Violet line.
    ui->impulseGraph->plotLayout()->addElement(1, 0, new QCPTextElement(ui->impulseGraph, "Impulse response", QFont("sans", 12)));
    //ui->impulseGraph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1), QBrush(Qt::white), 3));
    ui->impulseGraph->yAxis->setRange(-5, 5);
    ui->impulseGraph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                      QCP::iSelectLegend | QCP::iSelectPlottables);

    //connect(ui->frequencyGraph, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(FrequencyGraphClicked(QMouseEvent*)));

    RedrawGraphs(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool isPowerOfTwo(int sampleSize)
{
    double l2ss = log2((double)sampleSize);
    if(!(l2ss == (int)l2ss) || (sampleSize < 4))
    {
        QMessageBox msgBox;
        msgBox.setText("Please provide the N to be the power of 2.");
        msgBox.exec();
        return false;
    }
    return true;
}

void MainWindow::RedrawFIRGraphs(bool doRedrawSource)
{
    if(!isPowerOfTwo(ui->sampleSizeText->text().toInt())) return;

    ui->horizontalSlider->setMaximum(ui->sampleSizeText->text().toInt()/2 - 1);
    ui->frequencyText->setText(QString::number(ui->horizontalSlider->value()));

    vizualizer.SetSampleSize(ui->sampleSizeText->text().toInt());
    QCPTextElement* el = (QCPTextElement*)ui->frequencyGraph->plotLayout()->element(1, 0);
    el->setText("Frequency = " + QString::number(ui->horizontalSlider->value()));

    el = (QCPTextElement*)ui->impulseGraph->plotLayout()->element(1, 0);
    el->setText("Impulse response");

    double frequency = ui->horizontalSlider->value() + 1;
    if(doRedrawSource)
    {
        vizualizer.SetExpression(ui->equationText->text());
        el = (QCPTextElement*)ui->sourceGraph->plotLayout()->element(1, 0);

        QFontMetrics fm(ui->equationText->font());
        int width = fm.width(ui->equationText->text());
        static int truncatePos = 20;
        if(width+3 < ui->sourceGraph->width())
        {
            el->setText("y = " + ui->equationText->text());
            truncatePos = ui->equationText->text().size();
        }
        else
        {
            QString tempStr = ui->equationText->text();
            tempStr.truncate(truncatePos-3);
            el->setText("y = " + tempStr + "...");
        }

        vizualizer.DrawSinCosExpression(ui->sourceGraph);
    }
    vizualizer.DrawFIRGraph(ui->FIRGraph, frequency, ui->checkBox->isChecked());
    vizualizer.DrawFrequencyResponseGraph(ui->frequencyGraph, frequency, ui->checkBox->isChecked());
    vizualizer.DrawImpulseResponceGraph(ui->impulseGraph, frequency, ui->checkBox->isChecked());

    ui->FIRGraph->yAxis->setRange(ui->sourceGraph->yAxis->range());
}

void MainWindow::RedrawIIRGraphs(bool doRedrawSource)
{   
    if(!isPowerOfTwo(ui->sampleSizeText_2->text().toInt())) return;

    ui->horizontalSlider_2->setMaximum(ui->sampleSizeText_2->text().toInt()/2 - 1);
    ui->frequencyText_2->setText(QString::number(ui->horizontalSlider_2->value()));

    vizualizer.SetSampleSize(ui->sampleSizeText_2->text().toInt());
    QCPTextElement* el = (QCPTextElement*)ui->frequencyGraph->plotLayout()->element(1, 0);
    el->setText("Sample frequency response");

    el = (QCPTextElement*)ui->impulseGraph->plotLayout()->element(1, 0);
    el->setText("Filter frequency response");

    double frequency = ui->horizontalSlider_2->value();
    if(doRedrawSource)
    {
        vizualizer.SetExpression(ui->equationText_2->text());
        el = (QCPTextElement*)ui->sourceGraph->plotLayout()->element(1, 0);
        el->setText("y = " + ui->equationText_2->text());
        vizualizer.DrawSinCosExpression(ui->sourceGraph);
        vizualizer.DrawSourceFrequencyResponseGraph(ui->frequencyGraph);
    }

    vizualizer.DrawIIRGraph(ui->FIRGraph, frequency, ui->bwLineEdit->text().toDouble());
    vizualizer.DrawIIRFrequencyResponseGraph(ui->impulseGraph, frequency, ui->bwLineEdit->text().toDouble());

    ui->FIRGraph->yAxis->setRange(-1.1, 1.1);
}

void MainWindow::RedrawGraphs(bool doRedrawSource)
{
    enum GraphType
    {
        cGraphFIR = 0,
        cGraphIIR = 1,
    };

    if(ui->tabWidget->currentIndex() == cGraphFIR)
    {
        RedrawFIRGraphs(doRedrawSource);
    }
    else
    {
        RedrawIIRGraphs(doRedrawSource);
    }
}

void MainWindow::on_equationText_textEdited(const QString &arg1)
{
    QFontMetrics fm(ui->equationText->font());
    int width=fm.width(ui->equationText->text());
    if(width > ui->equationText->width())
    {
        ui->horizontalSlider->setVisible(false);
        ui->frequencyText->setVisible(false);
        ui->sampleSizeText->setVisible(false);
        ui->label_2->setVisible(false);
        ui->checkBox->setVisible(false);
    }
}

void MainWindow::on_equationText_returnPressed()
{
    ui->horizontalSlider->setVisible(true);
    ui->frequencyText->setVisible(true);
    ui->sampleSizeText->setVisible(true);
    ui->label_2->setVisible(true);
    ui->checkBox->setVisible(true);
    RedrawGraphs(true);
}

void MainWindow::on_sampleSizeText_returnPressed()
{
    if(ui->sampleSizeText->text().toInt() < 4)
    {
        ui->sampleSizeText->setText("4");
    }
    RedrawGraphs(true);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    RedrawGraphs();
}

void MainWindow::on_frequencyText_returnPressed()
{
    double frequency = ui->frequencyText->text().toDouble();
    double maxFrequency = ui->sampleSizeText->text().toDouble();

    if(frequency > maxFrequency)
    {
        frequency = maxFrequency;
    }
    else if (frequency < 1)
    {
        frequency = 1;
    }

    ui->horizontalSlider->setValue((int)frequency);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    RedrawGraphs();
}

void MainWindow::FrequencyGraphClicked(QMouseEvent* event)
{
    QCustomPlot* graph = ui->frequencyGraph;
    QPoint p = event->pos();
    double x, y;
    graph->graph(0)->pixelsToCoords((double)p.x(), (double)p.y(), x, y);

    x = round(x);
    cout << "CLICKED AT (" << x << ";" << y << ")" << endl;
    graph->graph(0)->addData(x, y);
    graph->replot();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    RedrawGraphs(true);
}

void MainWindow::on_equationText_2_textEdited(const QString &arg1)
{
    QFontMetrics fm(ui->equationText_2->font());
    int width=fm.width(ui->equationText_2->text());
    if(width > ui->equationText_2->width())
    {
        ui->horizontalSlider_2->setVisible(false);
        ui->frequencyText_2->setVisible(false);
        ui->sampleSizeText_2->setVisible(false);
        ui->bwLineEdit->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
    }
}

void MainWindow::on_equationText_2_returnPressed()
{
    ui->horizontalSlider_2->setVisible(true);
    ui->frequencyText_2->setVisible(true);
    ui->sampleSizeText_2->setVisible(true);
    ui->bwLineEdit->setVisible(true);
    ui->label_4->setVisible(true);
    ui->label_5->setVisible(true);
    RedrawGraphs(true);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    RedrawGraphs();
}

void MainWindow::on_frequencyText_2_returnPressed()
{
    double frequency = ui->frequencyText_2->text().toDouble();
    double maxFrequency = ui->sampleSizeText_2->text().toDouble();

    if(frequency > maxFrequency)
    {
        frequency = maxFrequency;
    }
    else if (frequency < 1)
    {
        frequency = 1;
    }

    ui->horizontalSlider_2->setValue((int)frequency);
}

void MainWindow::on_bwLineEdit_returnPressed()
{
    RedrawGraphs();
}

void MainWindow::on_sampleSizeText_2_returnPressed()
{
    if(ui->sampleSizeText_2->text().toInt() < 4)
    {
        ui->sampleSizeText_2->setText("4");
    }
    RedrawGraphs(true);
}



void MainWindow::on_equationText_2_selectionChanged()
{
}

void MainWindow::on_equationText_2_textChanged(const QString &arg1)
{

}


