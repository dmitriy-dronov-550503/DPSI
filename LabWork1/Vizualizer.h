#ifndef VIZUALIZER_H
#define VIZUALIZER_H
#include "qcustomplot.h"
#include "FourierTransform.h"
#include <complex>
#include <iostream>
using namespace std;

class Vizualizer
{
private:
    QVector<double> yValues;
    double ts;
    QString expression;
public:

    typedef enum Method
    {
        cDiscreteMethod,
        cFastMethod,
    } Mehtod;

    int sampleSize;
    Vizualizer(int sampleSize, QString expression);
    void SetExpression(QString expression);
    void DrawSinCosExpression(QCustomPlot* graph);
    void DrawForwardTransform(QCustomPlot* graph, Method method, FourierTransform::FFTMode mode);
    void DrawBackwardTransform(QCustomPlot* graph, Method method, FourierTransform::FFTMode mode);
    void DrawPhaseGraph(QCustomPlot* graph, Method method, FourierTransform::FFTMode mode);
};

#endif // VIZUALIZER_H
