#include "Processing.h"

#include <iostream>
using namespace std;

Processing::Processing()
{

}

QVector<double> Processing::Convolution(QVector<double> x, QVector<double> y)
{
    int sampleSize = x.size();
    QVector<double> z(sampleSize);
    for(int m = 0; m < sampleSize; m++)
    {
        for(int h = 0; h < sampleSize; h++)
        {
            int yi = m - h;
            if(yi < 0)
            {
                yi += sampleSize;
            }
            z[m] += x[h] * y[yi];
        }
        z[m] /= (sampleSize/2);
    }
    return z;
}

QVector<double> Processing::Correlation(QVector<double> x, QVector<double> y)
{
    int sampleSize = x.size();
    QVector<double> z(sampleSize);
    for(int m = 0; m < sampleSize; m++)
    {
        for(int h = 0; h < sampleSize; h++)
        {
            int yi = m + h;
            if(yi >= sampleSize)
            {
                yi -= sampleSize;
            }
            z[m] += x[h] * y[yi];
        }
        z[m] /= (sampleSize/2);
    }
    return z;
}

QVector<complex<double>> conjugate(QVector<complex<double>> vect)
{
    for(int i = 0; i < vect.size(); i++)
    {
        complex<double> conj(vect[i].real(), -1 * vect[i].imag());
        vect[i] = conj;
    }
    return vect;
}

QVector<double> Processing::ConvolutionFFT(QVector<double> x, QVector<double> y)
{
    int sampleSize = x.size();
    QVector<double> z(sampleSize);

    FourierTransform ft;
    QVector<complex<double>> Cx = ft.ForwardFastTransform(x);
    QVector<complex<double>> Cy = ft.ForwardFastTransform(y);

    QVector<complex<double>> Cz(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        Cz[i] = Cx[i] * Cy[i];
    }

    z = ft.BackwardFastTransform(Cz);

    return z;
}

QVector<double> Processing::CorrelationFFT(QVector<double> x, QVector<double> y)
{
    int sampleSize = x.size();
    QVector<double> z(sampleSize);

    FourierTransform ft;
    QVector<complex<double>> Cx = ft.ForwardFastTransform(x);
    QVector<complex<double>> Cy = ft.ForwardFastTransform(y);
    Cx = conjugate(Cx);

    QVector<complex<double>> Cz(sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        Cz[i] = Cx[i] * Cy[i];
    }

    z = ft.BackwardFastTransform(Cz);

    return z;
}
