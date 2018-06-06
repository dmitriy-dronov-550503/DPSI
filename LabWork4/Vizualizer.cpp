#include "Vizualizer.h"
#include "TimeMeasurement.h"
#include <QRegularExpression>
#include <QDebug>
#include <QJSEngine>
#include <iostream>
#include <iomanip>
#include <complex>
#include "Filter.h"
using namespace std;

#define VARIABLE_NAME(var) #var

Vizualizer::Vizualizer()
{
    this->sampleScale = 1;
}

void Vizualizer::SetSampleSize(int sampleSize)
{
    this->sampleSize = sampleSize;
    this->ts = (2 * M_PI * 1) / (sampleSize * sampleScale); // fs = 1. Base frequency in graph fs/N. fs = ws/2*pi -> ws = 2*pi*fs.
}

void Vizualizer::SetExpression(QString expression)
{
    this->expression = ProcessExpression(expression);
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

void Vizualizer::DrawSinCosExpression(QCustomPlot* graph1)
{
    bool replotFlag = true;
    QJSEngine engine;
    engine.evaluate("function rand(min, max) {return Math.round((Math.random() * (max - min) + min));}"
                    "R1 = rand(50,60); R2 = rand(70,80); R3 = rand(90,100)");
    QString test = "function test(y, max) { var sum = 0; for(i = 1; i < max; i++) { sum += (i/10) * Math.sin(i*y);} return sum; }";
    engine.evaluate(test);
    QVector<double> x(sampleSize);
    yValues1.resize(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        x[i] =  i;
        double yResult1 = engine.evaluate("x = " + QString::number(x[i] * ts) + ";"+expression).toNumber();
        yValues1[i] = yResult1;
        if(__builtin_isnan(yResult1))
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
    }
}


void Vizualizer::DrawFIRGraph(QCustomPlot* graph, double frequency, bool isHammingFunction)
{
    if(yValues1.size() < sampleSize) return;

    Filter ff;
    QVector<double> result(sampleSize);

    result = ff.FIRFilter(yValues1, frequency, isHammingFunction);

    //result = ff.IIRFilter(yValues1, frequency, sampleSize/2);

    QVector<double> x(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = (double)i;
    }

    graph->graph()->setData(x, result);
    graph->xAxis->rescale();
    //graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawFrequencyResponseGraph(QCustomPlot* graph, double frequency, bool isHammingFunction)
{
    if(yValues1.size() < sampleSize) return;

    Filter ff;
    QVector<double> FR;
    if(isHammingFunction)
    {
        FR = ff.GetImpulseResponceLow(sampleSize, frequency);
    }
    else
    {
        FR = ff.GetIdealImpulseResponceLow(sampleSize, frequency);
    }
    QVector<double> x = FourierTransform::MirrorTransformXValues(FR);

    FourierTransform ft;
    FR = ft.ForwardFastTransformAbs(FR);

    /*QVector<double> x(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = i;
    }*/

    graph->graph()->setData(x, FR);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawImpulseResponceGraph(QCustomPlot* graph, double frequency, bool isHammingFunction)
{
    Filter ff;
    QVector<double> IR;
    if(isHammingFunction)
    {
        IR = ff.GetImpulseResponceLow(sampleSize, frequency);
    }
    else
    {
        IR = ff.GetIdealImpulseResponceLow(sampleSize, frequency);
    }
    QVector<double> x = FourierTransform::MirrorTransformXValues(IR);

    graph->graph(0)->setData(x, IR);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}


void Vizualizer::DrawIIRGraph(QCustomPlot* graph, double frequency, double bandwidth)
{
    if(yValues1.size() < sampleSize) return;

    Filter ff;
    QVector<double> result(sampleSize);

    result = ff.IIRFilter(yValues1, frequency, bandwidth);

    QVector<double> x(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = (double)i;
    }

    graph->graph()->setData(x, result);
    graph->xAxis->rescale();
    //graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawSourceFrequencyResponseGraph(QCustomPlot* graph)
{
    if(yValues1.size() < sampleSize) return;

    FourierTransform ft;
    //QVector<double> sourceSampleFR = ft.ForwardFastTransformAbs(yValues1);
    //QVector<double> x = FourierTransform::MirrorTransformXValues(sourceSampleFR);

    QVector<double> sourceSampleFR = ft.ForwardDiscreteTransformAbs(yValues1);
    QVector<double> x(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = i;
    }

    graph->graph()->setData(x, sourceSampleFR);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawIIRFrequencyResponseGraph(QCustomPlot* graph, double frequency, double bandwidth)
{
    if(yValues1.size() < sampleSize) return;

    Filter ff;
    QVector<double> IIRFrequencyResponse = ff.GetIIRFrequencyResponse(sampleSize, frequency, bandwidth);
    QVector<double> x = FourierTransform::MirrorTransformXValues(IIRFrequencyResponse);

    /*QVector<double> x(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = i;
    }*/

    graph->graph()->setData(x, IIRFrequencyResponse);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

