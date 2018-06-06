#ifndef FOURIER_H
#define FOURIER_H
#include <complex>
#include <QVector>
using namespace std;

class FourierTransform
{
public:
    typedef enum FFTMode
    {
        decimationInTime,
        decimationInFrequency,
    } FFTMode;

private:
    const double forward = 1;
    const double backward = -1;
    FFTMode mode;

public:
    FourierTransform();
    FourierTransform(FFTMode mode);
    QVector<complex<double>> ForwardDiscreteTransform(QVector<double> sample);
    QVector<complex<double>> ForwardDiscreteTransform(QVector<complex<double>> sample);
    QVector<double> ForwardDiscreteTransformAbs(QVector<double> sample);
    QVector<double> BackwardDiscreteTransform(QVector<complex<double>> sample);
    QVector<complex<double>> ForwardFastTransform(QVector<double> sample);
    QVector<complex<double>> ForwardFastTransform(QVector<complex<double>> sample);
    QVector<double> ForwardFastTransformAbs(QVector<double> sample);
    QVector<double> BackwardFastTransform(QVector<complex<double>> sample);
    QVector<double> BackwardFastTransform(QVector<double> sample);
    static QVector<double> MirrorTransform(QVector<double> sample);
    static QVector<double> MirrorTransformXValues(QVector<double> sample);
private:
    QVector<complex<double>> DiscreteTransform(QVector<complex<double>> sample, double direction);
    QVector<complex<double>> FastTransform(QVector<complex<double>> sample, double direction);
    QVector<complex<double>> FastTransformDecimationInTime(QVector<complex<double>> sample, double direction, bool firstIteration);
    QVector<complex<double>> FastTransformDecimationInFrequency(QVector<complex<double>> sample, double direction, bool firstIteration);
    QVector<complex<double>> ConvertToComplex(QVector<double> sample);

};



#endif // FOURIER_H
