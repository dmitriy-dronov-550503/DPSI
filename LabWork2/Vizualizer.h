#ifndef VIZUALIZER_H
#define VIZUALIZER_H
#include "qcustomplot.h"
#include "FourierTransform.h"
#include "Processing.h"
#include <complex>
#include <iostream>
using namespace std;

class Vizualizer
{
private:
    QVector<double> yValues1, yValues2;
    double ts;
    QString expression1, expression2;
    double sampleScale;
public:

    typedef enum Method
    {
        cGenericMethod,
        cFFTMethod,
    } Mehtod;

    int sampleSize;
    Vizualizer(int sampleSize, QString expression1, QString expression2);
    QString ProcessExpression(QString expression);
    void DrawSinCosExpression(QCustomPlot* graph1, QCustomPlot* graph2);
    void DrawConvolutionGraph(QCustomPlot* graph, Method method);
    void DrawCorrelationGraph(QCustomPlot* graph, Method method);
    void DrawResultGraph(QCustomPlot* graph, Method method);
};

#endif // VIZUALIZER_H
