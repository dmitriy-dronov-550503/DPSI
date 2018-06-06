#ifndef FILTER_H
#define FILTER_H
#include <QVector>
#include <math.h>
#include <iostream>
using namespace std;

class Filter
{
public:
    Filter();
    QVector<double> FIRFilter(QVector<double> sample, double frequency, bool isHammingFunction);
    QVector<double> IIRFilter(QVector<double> sample, double frequency, double bandwidth);

    QVector<double> GetFrequencyResponse(int N, double bandwithLow, double bandwithHigh);
    QVector<double> GetFrequencyResponseLow(int N, double frequency);
    QVector<double> GetFrequencyResponseHigh(int N, double frequency);

    QVector<double> GetIdealImpulseResponce(int N, double bandwithLow, double bandwithHigh);
    QVector<double> GetIdealImpulseResponce2(int N, double bandwithLow, double bandwithHigh);

    QVector<double> GetIdealImpulseResponceLow(int N, double frequency);
    QVector<double> GetIdealImpulseResponceHigh(int N, double frequency);


    QVector<double> GetImpulseResponce(int N, double bandwithLow, double bandwithHigh);
    QVector<double> GetImpulseResponceLow(int N, double frequency);
    QVector<double> GetImpulseResponceHigh(int N, double frequency);

    QVector<double> HammingFunction(QVector<double> sample);
    QVector<double> GetHammingCoefficients(int N);

    QVector<double> GetIIRFrequencyResponse(int N, double frequency, double bandwidth);


};

#endif // FILTER_H
