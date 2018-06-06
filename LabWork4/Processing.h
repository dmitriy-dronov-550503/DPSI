#ifndef PROCESSING_H
#define PROCESSING_H
#include <QVector>
#include "FourierTransform.h"

class Processing
{
public:
    Processing();

    QVector<double> Convolution(QVector<double> x, QVector<double> y);
    QVector<double> Correlation(QVector<double> x, QVector<double> y);
    QVector<double> ConvolutionFFT(QVector<double> x, QVector<double> y);
    QVector<double> CorrelationFFT(QVector<double> x, QVector<double> y);
};

#endif // PROCESSING_H
