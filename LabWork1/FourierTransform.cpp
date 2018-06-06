#include "FourierTransform.h"
#include <QDebug>
#include <iostream>
#include <iomanip>
#include <complex>
using namespace std;

FourierTransform::FourierTransform()
{
    this->mode = decimationInFrequency;
}

FourierTransform::FourierTransform(FFTMode mode)
{
    this->mode = mode;
}

QVector<complex<double>> FourierTransform::DiscreteTransform(QVector<complex<double>> sample, double direction)
{
    int sampleSize = sample.size();
    QVector<complex<double>> resultSample(sampleSize);
    for(int k = 0; k < sampleSize; k++)
    {
        complex<double> sum(0.0, 0.0);
        const double N = (double)sampleSize;
        const complex<double> minusOneI = complex<double>(0.0, -1.0);
        const complex<double> W = exp((minusOneI * 2.0 * M_PI) / N);

        for(int m = 0; m < sampleSize; m++)
        {
            complex<double> var = sample[m] * pow(W, direction * k * m);
            sum += var;
        }

        if(direction == forward)
        {
            resultSample[k] = sum / (N / 2);
        }
        else
        {
            resultSample[k] = sum / 2.0;
        }
    }
    return resultSample;
}

QVector<complex<double>> FourierTransform::FastTransform(QVector<complex<double>> sample, double direction)
{
    switch(mode)
    {
    case decimationInTime:
        return FastTransformDecimationInTime(sample, direction, true);
        break;
    case decimationInFrequency:
        return FastTransformDecimationInFrequency(sample, direction, true);
        break;
    }
}

QVector<complex<double>> FourierTransform::FastTransformDecimationInTime(QVector<complex<double>> sample, double direction, bool firstIteration)
{
    int sampleSize = sample.size();
    if(sampleSize == 1) return sample;

    QVector<complex<double>> even(sampleSize/2), odd(sampleSize/2);

    for(int i = 0; i < sampleSize; i++)
    {
        if(i%2==0)
        {
            even[i/2] = sample[i];
        }
        else
        {
            odd[((i+1)/2)-1] = sample[i];
        }
    }

    even = FastTransformDecimationInTime(even, direction, false);
    odd = FastTransformDecimationInTime(odd, direction, false);

    const complex<double> OneI(0.0, 1.0);
    const complex<double> N(sampleSize, 0.0);
    const complex<double> WN = exp((2.0 * M_PI * direction * OneI) / N);
    complex<double> W(1.0, 0.0);
    QVector<complex<double>> result(sampleSize);

    complex<double> NN(1.0, 0.0);
    if(firstIteration)
    {
        if(direction == forward)
        {
            NN = sampleSize/2.0;
        }
        else
        {
            NN = 2;
        }
    }

    for(int i = 0; i < sampleSize/2; i++)
    {
        result[i] = even[i] + (W * odd[i]);
        result[i] /= NN;
        result[i + (sampleSize/2)] = even[i] - (W * odd[i]);
        result[i + (sampleSize/2)] /= NN;
        W = W * WN;
    }

    return result;
}

QVector<complex<double>> FourierTransform::FastTransformDecimationInFrequency(QVector<complex<double>> sample, double direction, bool firstIteration)
{
    int sampleSize = sample.size();
    if(sampleSize == 1) return sample;

    const complex<double> OneI(0.0, 1.0);
    const complex<double> N(sampleSize, 0.0);
    const complex<double> WN = exp((2.0* M_PI * direction * OneI) / N);
    complex<double> W(1.0, 0.0);
    QVector<complex<double>> b(sampleSize/2), c(sampleSize/2);

    for(int i = 0; i < sampleSize/2; i++)
    {
        b[i] = sample[i] + sample[i + (sampleSize/2)];
        c[i] = (sample[i] - sample[i + (sampleSize/2)]) * W;
        W = W * WN;
    }

    b = FastTransformDecimationInFrequency(b, direction, false);
    c = FastTransformDecimationInFrequency(c, direction, false);

    QVector<complex<double>> result(sampleSize);

    complex<double> NN(1.0, 0.0);
    if(firstIteration)
    {
        if(direction == forward)
        {
            NN = sampleSize/2.0;
        }
        else
        {
            NN = 2;
        }
    }

    for(int i = 0; i < sampleSize/2; i++)
    {
        result[i*2] = b[i] / NN;
    }
    for(int i = 0; i < sampleSize/2; i++)
    {
        result[((i+2)*2)-3] = c[i] / NN;
    }

    return result;
}

QVector<complex<double>> FourierTransform::ConvertToComplex(QVector<double> sample)
{
    QVector<complex<double>> result(sample.size());
    for(int i = 0; i < sample.size(); i++)
    {
        complex<double> temp(sample[i], 0);
        result[i] = temp;
    }
    return result;
}

QVector<complex<double>> FourierTransform::ForwardDiscreteTransform(QVector<double> sample)
{
    QVector<complex<double>> sampleComplex = ConvertToComplex(sample);
    return DiscreteTransform(sampleComplex, forward);
}

QVector<complex<double>> FourierTransform::ForwardDiscreteTransform(QVector<complex<double>> sample)
{
    return DiscreteTransform(sample, forward);
}

QVector<complex<double>> FourierTransform::BackwardDiscreteTransform(QVector<double> sample)
{
    QVector<complex<double>> sampleComplex = ConvertToComplex(sample);
    return DiscreteTransform(sampleComplex, backward);
}

QVector<complex<double>> FourierTransform::BackwardDiscreteTransform(QVector<complex<double>> sample)
{
    return DiscreteTransform(sample, backward);
}

QVector<complex<double>> FourierTransform::ForwardFastTransform(QVector<double> sample)
{
    QVector<complex<double>> sampleComplex = ConvertToComplex(sample);
    return FastTransform(sampleComplex, forward);
}

QVector<complex<double>> FourierTransform::ForwardFastTransform(QVector<complex<double>> sample)
{
    return FastTransform(sample, forward);
}

QVector<complex<double>> FourierTransform::BackwardFastTransform(QVector<double> sample)
{
    QVector<complex<double>> sampleComplex = ConvertToComplex(sample);
    return FastTransform(sampleComplex, backward);
}

QVector<complex<double>> FourierTransform::BackwardFastTransform(QVector<complex<double>> sample)
{
    return FastTransform(sample, backward);
}
