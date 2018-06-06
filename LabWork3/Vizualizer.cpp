#include "Vizualizer.h"
#include "TimeMeasurement.h"
#include <QRegularExpression>
#include <QDebug>
#include <QJSEngine>
#include <iostream>
#include <iomanip>
#include <complex>
using namespace std;

Vizualizer::Vizualizer(int sampleSize, QString expression, bool inDoShuffleInTransform)
{
    this->sampleSize = sampleSize;
    this->ts = M_PI / sampleSize; // fs = 1. Base frequency in graph fs/N. fs = ws/2*pi -> ws = 2*pi*fs.
    this->doShuffleInTransform = inDoShuffleInTransform;
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
    QVector<double> x(sampleSize);
    yValues.resize(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        x[i] =  i;
        double yResult = engine.evaluate("x = " + QString::number(x[i] * ts) + ";"+expression).toNumber();
        yValues[i] = yResult;
        if(isnan(yResult))
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

void Vizualizer::DrawForwardTransform(QCustomPlot* graph, Method method)
{
    if(yValues.size() < sampleSize) return;

    WalshTransform wt(doShuffleInTransform);
    QVector<double> y;
    TimeChrono time;
    string nameOfMethod = "";
    time.start();
    switch(method)
    {
    case cDiscreteMethod:
        y = wt.ForwardDiscreteTransform(yValues);
        nameOfMethod = "DISCRETE transform : \t";
        break;
    case cFastMethod:
        y = wt.ForwardFastTransform(yValues);
        nameOfMethod = "FAST transform : \t\t";
        break;
    }
    time.stop();
    cout << "Forward transform time for " << nameOfMethod << time.getResult() << endl;
    //QMessageBox msgBox;
    //msgBox.setText("Forward transform time: " + QString::number(time.getResult()/1000) + " ns");
    //msgBox.exec();

    QVector<double> x(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = (double)i;
    }

    graph->graph()->setData(x, y);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}

void Vizualizer::DrawBackwardTransform(QCustomPlot* graph, Method method)
{
    WalshTransform wt(doShuffleInTransform);
    QVector<double> y;
    switch(method)
    {
    case cDiscreteMethod:
        y = wt.BackwardDiscreteTransform(wt.ForwardDiscreteTransform(yValues));
        break;
    case cFastMethod:
        y = wt.BackwardFastTransform(wt.ForwardFastTransform(yValues));
        break;
    }

    QVector<double> x(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        x[i] = (double)i;
    }

    graph->graph()->setData(x, y);
    graph->xAxis->rescale();
    graph->yAxis->rescale();
    graph->replot();
}




