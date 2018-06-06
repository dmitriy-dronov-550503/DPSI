#include "Vizualizer.h"
#include "TimeMeasurement.h"
#include <QRegularExpression>
#include <QDebug>
#include <QJSEngine>
#include <iostream>
#include <iomanip>
#include <complex>
using namespace std;

Vizualizer::Vizualizer(int sampleSize, QString expression)
{
    this->sampleSize = sampleSize;
    this->ts = (2 * M_PI * 1) / sampleSize; // fs = 1. Base frequency in graph fs/N. fs = ws/2*pi -> ws = 2*pi*fs.
    SetExpression(expression);
}

void Vizualizer::SetExpression(QString expression)
{
    expression = expression.replace("sin", "Math.sin");
    expression = expression.replace("cos", "Math.cos");
    expression = expression.replace("ctg", "1 / Math.tan");
    expression = expression.replace("tg", "Math.tan");
    this->expression = expression;
}

void Vizualizer::DrawSinCosExpression(QCustomPlot* graph)
{
    bool replotFlag = true;
    QJSEngine engine;
    QString test = "function test(y, max) { var sum = 0; for(i = 1; i < max; i++) { sum += (i/10) * Math.sin(i*y);} return sum; }";
    engine.evaluate(test);
    QVector<double> x(sampleSize);
    yValues.resize(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        x[i] =  i;
        double yResult = engine.evaluate("x = " + QString::number(x[i] * ts) + ";"+expression).toNumber();
        yValues[i] = yResult;
        if(__builtin_isnan(yResult))
        {
            replotFlag = false;
            break;
        };
    }

    if(replotFlag)
    {
        graph->graph()->setData(x, yValues);
        graph->xAxis->rescale();
        graph->yAxis->rescale();
        graph->replot();
    }
}

void Vizualizer::DrawForwardTransform(QCustomPlot* graph, Method method, FourierTransform::FFTMode mode)
{
    if(yValues.size() < sampleSize) return;

    FourierTransform ft(mode);
    QVector<complex<double>> y;
    TimeChrono time;
    string nameOfMethod = "";
    time.start();
    switch(method)
    {
    case cDiscreteMethod:
        y = ft.ForwardDiscreteTransform(yValues);
        nameOfMethod = "DISCRETE transform : \t";
        break;
    case cFastMethod:
        y = ft.ForwardFastTransform(yValues);
        nameOfMethod = "FAST transform : \t\t";
        break;
    }
    time.stop();
    cout << "Forward transform time for " << nameOfMethod << time.getResult() << endl;
    //QMessageBox msgBox;
    //msgBox.setText("Forward transform time: " + QString::number(time.getResult()/1000) + " ns");
    //msgBox.exec();

    QVector<double> x(sampleSize), y2(sampleSize);

    for(int i = 0; i < sampleSize/2; i++)
    {
        x[i] = (double)i;
        y2[i] = std::abs(y[i]);
    }

    for(int i = sampleSize/2; i < sampleSize; i++)
    {
        x[i] = ((double)i - sampleSize);
        y2[i] = std::abs(y[i]);
    }

    graph->graph()->setData(x, y2);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawBackwardTransform(QCustomPlot* graph, Method method, FourierTransform::FFTMode mode)
{
    FourierTransform ft(mode);
    QVector<complex<double>> y;
    switch(method)
    {
    case cDiscreteMethod:
        y = ft.BackwardDiscreteTransform(ft.ForwardDiscreteTransform(yValues));
        break;
    case cFastMethod:
        y = ft.BackwardFastTransform(ft.ForwardFastTransform(yValues));
        break;
    }

    QVector<double> x(sampleSize), y2(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = (double)i;
        y2[i] = y[i].real();
    }

    graph->graph()->setData(x, y2);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawPhaseGraph(QCustomPlot* graph, Method method, FourierTransform::FFTMode mode)
{
    FourierTransform ft(mode);
    QVector<complex<double>> y;
    switch(method)
    {
    case cDiscreteMethod:
        y = ft.ForwardDiscreteTransform(yValues);
        break;
    case cFastMethod:
        y = ft.ForwardFastTransform(yValues);
        break;
    }

    QVector<double> x(sampleSize), y2(sampleSize);
    for(int i = 0; i < sampleSize/2; i++)
    {
        x[i] = (double)i;
        //y2[i] = std::arg(y[i]);
        y2[i] = atan(y[i].imag() / std::abs(y[i]));
    }

    for(int i = sampleSize/2; i < sampleSize; i++)
    {
        x[i] = (double)i - sampleSize;
        //y2[i] = std::arg(y[i]);
        y2[i] = atan(y[i].imag() / std::abs(y[i]));
    }
    graph->graph()->setData(x, y2);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}


