#include "Filter.h"
#include "Processing.h"

Filter::Filter()
{

}

QVector<double> Filter::GetHammingCoefficients(int N)
{
    QVector<double> Ham(N);
    for(int i = 0; i < N; i++)
    {
        Ham[i] = 0.54 + 0.46 * cos((2 * M_PI * i) / (N - 1));
    }
    return Ham;
}


QVector<double> Filter::GetFrequencyResponse(int N, double bandwithLow, double bandwithHigh)
{
    QVector<double> FR(N);

    for(int i = 0; i < bandwithLow; i++)
    {
        FR[i] = 0;
        FR[N-1-i] = 0;
    }

    for(int i = (int)bandwithLow; i < bandwithHigh; i++)
    {
        FR[i] = 1;
        FR[N-1-i] = 1;
    }

    // FR[N - frequency] will be overwritten with 0. Regards to graph in Richard Lions book.
    for(int i = (int)bandwithHigh; i < (N - bandwithHigh) + 1; i++)
    {
        FR[i] = 0;
    }

    return FR;
}

QVector<double> Filter::GetFrequencyResponseLow(int N, double frequency)
{
    return GetFrequencyResponse(N, 0, frequency);
}

QVector<double> Filter::GetFrequencyResponseHigh(int N, double frequency)
{
    return GetFrequencyResponse(N, frequency, N/2);
}


QVector<double> Filter::GetIdealImpulseResponce2(int N, double bandwithLow, double bandwithHigh)
{
    double BW = (bandwithHigh - bandwithLow)/N;
    double M = 4 / BW;
    double fc = bandwithLow/N;

    QVector<double> H_ideal(M + 1);

    for(int i = 0; i < M; i++)
    {
        if((i-M)/2 == 0)
        {
            H_ideal[i] = 2 * M_PI * fc;
        }
        else
        {
            H_ideal[i] = sin(2*M_PI*fc*(i-M/2)) / (i-M/2);
        }
        H_ideal[i] = H_ideal[i] * (0.42 - 0.5*cos(2*M_PI*i/M) + 0.08*cos(4*M_PI*i/M));
    }

    H_ideal.resize(N);
    return H_ideal;
}

QVector<double> Filter::GetIdealImpulseResponce(int N, double bandwithLow, double bandwithHigh)
{
    QVector<double> H_ideal = GetFrequencyResponse(N, bandwithLow, bandwithHigh);
    FourierTransform ft;
    H_ideal = ft.BackwardFastTransform(H_ideal);

    return H_ideal;
}

QVector<double> Filter::GetIdealImpulseResponceLow(int N, double frequency)
{
    return GetIdealImpulseResponce(N, 0, frequency);
}

QVector<double> Filter::GetIdealImpulseResponceHigh(int N, double frequency)
{
    return GetIdealImpulseResponce(N, frequency, N/2);
}


QVector<double> Filter::GetImpulseResponce(int N, double bandwithLow, double bandwithHigh)
{
    return HammingFunction(GetIdealImpulseResponce(N, bandwithLow, bandwithHigh));
}

QVector<double> Filter::GetImpulseResponceLow(int N, double frequency)
{
    return GetImpulseResponce(N, 0, frequency);
}

QVector<double> Filter::GetImpulseResponceHigh(int N, double frequency)
{
    return GetImpulseResponce(N, frequency, N/2);
}


QVector<double> Filter::HammingFunction(QVector<double> sample)
{
    int N = sample.size();
    for(int i = 0; i < N; i++)
    {
        double W = 0.54 + 0.46 * cos((2 * M_PI * i) / (N - 1));
        sample[i] = sample[i] * W;
    }
    /*for(int i = 20; i < N-20; i++) // Use it to show the FIR distortions
    {
        sample[i] = 0;
    }*/
    return sample;
}

QVector<double> Filter::FIRFilter(QVector<double> sample, double frequency, bool isHammingFunction = true)
{
    int sampleSize = sample.size();

    QVector<double> H = GetIdealImpulseResponceLow(sampleSize, frequency);

    if(isHammingFunction)
    {
        H = HammingFunction(H);
    }

    Processing pr;
    QVector<double> out = pr.ConvolutionFFT(H, sample);

    return out;
}

QVector<double> Filter::IIRFilter(QVector<double> sample, double frequency, double bandwidth)
{
    int N = sample.size();
    QVector<double> Y(N);
    for(int i = 0; i < N; i++)
    {
        Y[i] = 0;
    }

    double f = 2 * M_PI * (frequency/N);

    double BW = (bandwidth/(double)N); // divide by 0.707 to wider range
    double R = 1 - 3*BW;
    double K = (1 - 2*R*cos(f) + pow(R, 2)) / (2 - 2*cos(f));
    double a0 = 1 - K;
    double a1 = 2 * (K - R) * cos(f);
    double a2 = pow(R, 2) - K;
    double b1 = 2 * R * cos(f);
    double b2 = -1 * pow(R, 2);

    for(int i = 2; i < N; i++)
    {
        //cout << "before " << Y[i-1] << " ";
        Y[i] = a0*sample[i] + a1*sample[i-1] + a2*sample[i-2] + b1*Y[i-1]+ b2*Y[i-2];
        //cout << "after " << Y[i] << endl;
    }



    return Y;
}

QVector<double> Filter::GetIIRFrequencyResponse(int N, double frequency, double bandwidth)
{
    QVector<double> H_real(N);

    QVector<double> delta(N);
    delta[0] = 1;
    for(int i = 1; i < N; i++)
    {
        delta[i] = 0;
    }

    H_real = IIRFilter(delta, frequency, bandwidth);

    FourierTransform ft;
    H_real = ft.ForwardFastTransformAbs(H_real);

    return H_real;
}
