#include "Vizualizer.h"
#include "TimeMeasurement.h"
#include <QRegularExpression>
#include <QDebug>
#include <QJSEngine>
#include <iostream>
#include <iomanip>
#include <complex>
using namespace std;

#define VARIABLE_NAME(var) #var

Vizualizer::Vizualizer(int sampleSize, QString expression1, QString expression2)
{
    this->sampleSize = sampleSize;
    this->sampleScale = 1;
    this->ts = (2 * M_PI * 1) / (sampleSize * sampleScale); // fs = 1. Base frequency in graph fs/N. fs = ws/2*pi -> ws = 2*pi*fs.
    this->expression1 = ProcessExpression(expression1);
    this->expression2 = ProcessExpression(expression2);
}

QString Vizualizer::ProcessExpression(QString expression)
{
    expression = expression.replace("sin", "Math.sin");
    expression = expression.replace("cos", "Math.cos");
    expression = expression.replace("ctg", "1 / Math.tan");
    expression = expression.replace("tg", "Math.tan");
    expression = expression.replace("exp", "Math.exp");
    expression = expression.replace("log", "Math.log");
    expression = expression.replace("sign", "Math.sign");
    expression = expression.replace("PI", "Math.PI");
    expression = expression.replace("E", "Math.E");
    return expression;
}

void Vizualizer::DrawSinCosExpression(QCustomPlot* graph1, QCustomPlot* graph2)
{
    bool replotFlag = true;
    QJSEngine engine;
    QVector<double> x(sampleSize);
    yValues1.resize(sampleSize);
    yValues2.resize(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        x[i] =  i;
        double yResult1 = engine.evaluate("x = " + QString::number(x[i] * ts) + ";"+expression1).toNumber();
        double yResult2 = engine.evaluate("x = " + QString::number(x[i] * ts) + ";"+expression2).toNumber();
        yValues1[i] = yResult1;
        yValues2[i] = yResult2;
        if(isnan(yResult1) || isnan(yResult2))
        {
            replotFlag = false;
            break;
        };
    }

    if(replotFlag)
    {
        graph1->graph(0)->setData(x, yValues1);
        graph1->xAxis->rescale();
        graph1->yAxis->rescale();
        graph1->replot();

        graph2->graph(0)->setData(x, yValues2);
        graph2->xAxis->rescale();
        graph2->yAxis->rescale();
        graph2->replot();
    }
}

void Vizualizer::DrawConvolutionGraph(QCustomPlot* graph, Method method)
{
    if(yValues1.size() < sampleSize) return;

    Processing pr;
    FourierTransform ft;
    QVector<double> z(sampleSize);
    switch(method)
    {
    case cGenericMethod:
        z = pr.Convolution(yValues1, yValues2);
        cout << "Generic convolution completed." << endl;
        break;
    case cFFTMethod:
        z = pr.ConvolutionFFT(yValues1, yValues2);
        cout << "FFT convolution completed." << endl;
        break;
    }

    QVector<double> x(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = (double)i;
    }

    graph->graph()->setData(x, z);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawCorrelationGraph(QCustomPlot* graph, Method method)
{
    if(yValues1.size() < sampleSize) return;

    Processing pr;
    FourierTransform ft;
    QVector<double> z(sampleSize);
    switch(method)
    {
    case cGenericMethod:
        z = pr.Correlation(yValues1, yValues2);
        cout << "Generic correlation completed." << endl;
        break;
    case cFFTMethod:
        z = pr.CorrelationFFT(yValues1, yValues2);
        cout << "FFT correlation completed." << endl;
        break;
    }

    QVector<double> x(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = (double)i;
    }

    graph->graph()->setData(x, z);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawResultGraph(QCustomPlot* graph, Method method)
{

    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}


