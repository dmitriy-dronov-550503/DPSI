#ifndef VIZUALIZER_H
#define VIZUALIZER_H
#include "qcustomplot.h"
#include "WalshTransform.h"
#include <complex>
#include <iostream>
using namespace std;

class Vizualizer
{
private:
    QVector<double> yValues;
    double ts;
    QString expression;
    bool doShuffleInTransform;
public:

    typedef enum Method
    {
        cDiscreteMethod,
        cFastMethod,
    } Mehtod;

    int sampleSize;
    Vizualizer(int sampleSize, QString expression, bool inDoShuffleInTransform);
    void SetExpression(QString expression);
    void DrawSinCosExpression(QCustomPlot* graph);
    void DrawForwardTransform(QCustomPlot* graph, Method method);
    void DrawBackwardTransform(QCustomPlot* graph, Method method);
};

#endif // VIZUALIZER_H
