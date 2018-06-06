#ifndef FOURIER_H
#define FOURIER_H
#include <complex>
#include <QVector>
using namespace std;

class WalshTransform
{
private:
    const double forward = 1;
    const double backward = -1;
    bool doAdamarToWalshShuffle;
public:
    WalshTransform(bool inDoAdamarToWalshShuffle);
    QVector<double> ForwardDiscreteTransform(QVector<double> sample);
    QVector<double> BackwardDiscreteTransform(QVector<double> sample);
    QVector<double> ForwardFastTransform(QVector<double> sample);
    QVector<double> BackwardFastTransform(QVector<double> sample);
private:
    QVector<double> DiscreteTransform(QVector<double> sample, double direction);
    QVector<double> FastTransform(QVector<double> sample, double direction);
};



#endif // FOURIER_H
