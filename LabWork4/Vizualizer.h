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
    QString expression, expression2;
    double sampleScale;
public:

    typedef enum Method
    {
        cGenericMethod,
        cFFTMethod,
    } Mehtod;

    int sampleSize;
    Vizualizer();
    void SetSampleSize(int sampleSize);
    void SetExpression(QString expression);
    QString ProcessExpression(QString expression);
    void DrawSinCosExpression(QCustomPlot* graph1);

    void DrawFIRGraph(QCustomPlot* graph, double frequency, bool isHammingFunction);
    void DrawFrequencyResponseGraph(QCustomPlot* graph, double frequency, bool isHammingFunction);
    void DrawImpulseResponceGraph(QCustomPlot* graph, double frequency, bool isHammingFunction);

    void DrawIIRGraph(QCustomPlot* graph, double frequency, double bandwidth);
    void DrawSourceFrequencyResponseGraph(QCustomPlot* graph);
    void DrawIIRFrequencyResponseGraph(QCustomPlot* graph, double frequency, double bandwidth);
};

#endif // VIZUALIZER_H
