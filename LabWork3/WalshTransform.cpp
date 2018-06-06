#include "WalshTransform.h"
#include <QDebug>
#include <iostream>
#include <iomanip>
#include <complex>
#include <math.h>
#include <bitset>
#include "Matrix.h"
#include "MatrixMultiply.h"
using namespace std;

void show(double** matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }
}

unsigned int reverseBits(unsigned int num, unsigned int numberOfBits)
{
    //unsigned int  NO_OF_BITS = sizeof(num) * 8;
    unsigned int  NO_OF_BITS = numberOfBits;
    unsigned int reverse_num = 0;
    int i;
    for (i = 0; i < NO_OF_BITS; i++)
    {
        if((num & (1 << i)))
           reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
   }
    return reverse_num;
}

unsigned int binaryToGray(unsigned int num)
{
    return (num >> 1) ^ num;
}

unsigned int grayToBinary(unsigned int num)
{
    for(int i = 16; i != 0; i = i >> 1)
    {
        num ^= (num >> i);
    }
    return num;
}

double sign(double x)
{
    return x >=0.0 ? 1.0 : -1.0;
}

QVector<double> rademacher(int k, int sampleSize)
{
    QVector<double> radm(sampleSize);
    for(int t = 0; t < sampleSize; t++)
    {
        radm[t] = sign(sin(pow(2, k) * M_PI * (double)t/(sampleSize - 1)));
    }
    return radm;
}

// n - rowNumber.
QVector<double> walshLine(int n, int sampleSize)
{
    QVector<double> result = rademacher(0, sampleSize);
    int mask = binaryToGray(n);

    for(int k = 1; k < sqrt(sampleSize)+1; k++)
    {
        if(((1 << (k - 1)) & mask) != 0)
        {
            QVector<double> radm = rademacher(k, sampleSize);
            for(int i = 0; i < sampleSize; i++)
            {
                result[i] = result[i]*radm[i];
            }
        }
    }
    return result;
}

void walsh(double** e, int sampleSize)
{
    for(int i = 0; i < sampleSize; i++)
    {
        QVector<double> result = walshLine(i, sampleSize);
        for(int j = 0; j < sampleSize; j++)
        {
            e[i][j] = result[j];
        }
    }
}

QVector<double> hadamardToWalshShuffle(QVector<double> sample)
{
    unsigned int sampleSize = sample.size();
    QVector<double> result(sampleSize);

    for(int i = 0; i < sampleSize; i++)
    {
        unsigned int rightIndex = grayToBinary(reverseBits(i, log2(sampleSize)));
        result[rightIndex] = sample[i];
    }

    return result;
}

WalshTransform::WalshTransform(bool inDoAdamarToWalshShuffle)
{
    this->doAdamarToWalshShuffle = inDoAdamarToWalshShuffle;
}

int getSign(unsigned int N) {
    int i;
    for (i = 0; N; N >>= 1)
    {
        i += N & 1;
    }
    return (i & 1) ? -1 : 1;
}

void hadamard(double **e, unsigned int sampleSize) {
    for (unsigned int i = 0; i < sampleSize; ++i)
    {
        for (unsigned int j = 0; j < sampleSize; ++j)
        {
            e[i][j] = getSign(i & j);
        }
    }
}

void reorder(double** e, int sampleSize)
{
    Matrix<double> temp(sampleSize, sampleSize);
    for(int i = 0; i < sampleSize; i++)
    {
        int changes = 0;
        for(int j = 1; j < sampleSize; j++)
        {
            if(e[i][j-1] != e[i][j]) changes++;
        }
        cout << changes << endl;
        for(int j = 0; j < sampleSize; j++)
        {
            temp.ptr[changes][j] = e[i][j];
        }
    }

    for(int i = 0; i < sampleSize; i++)
    {
        for(int j = 0; j < sampleSize; j++)
        {
            e[i][j] = temp.ptr[i][j];
        }
    }
}

QVector<double> WalshTransform::DiscreteTransform(QVector<double> sample, double direction)
{
    int sampleSize = sample.size();

    Matrix<double> mx(sampleSize, sampleSize); // WALSH MATRIX
    //walsh(mx.ptr, sampleSize);
    hadamard(mx.ptr, sampleSize);
    //reorder(mx.ptr, sampleSize);

    Matrix<double> mxs(1, sampleSize); // SAMPLE VECTOR
    for(int i = 0; i < sampleSize; i++)
    {
        mxs.ptr[0][i] = sample[i];
    }

    Matrix<double> res(1, sampleSize); // RESULT OF WALSH TRANSFORM VECTOR
    MatrixMultiply<double>::multiply(mxs.ptr, mx.ptr, res.ptr, mxs.m, mxs.n, mx.m, mx.n);

    if(direction == backward)
    {
        for(int i = 0; i < sampleSize; i++)
        {
            sample[i] = res.ptr[0][i];
        }
    }
    else
    {
        for(int i = 0; i < sampleSize; i++)
        {
            sample[i] = res.ptr[0][i] / sampleSize;
        }
    }

    return sample;
}

QVector<double> WalshTransform::FastTransform(QVector<double> sample, double direction)
{    
    if (sample.size() == 1)
    {
        return sample;
    }

    int N = sample.size();

    QVector<double> left(N / 2);
    QVector<double> right(N / 2);

    for (int j = 0; j < N / 2; j++)
    {
        left[j] = sample[j] + sample[j + N / 2];
        right[j] = sample[j] - sample[j + N / 2];
    }

    QVector<double> b_left = FastTransform(left, direction);
    QVector<double> b_right = FastTransform(right, direction);

    QVector<double> y(N);
    if (direction == forward)
    {
        for (int j = 0; j < N / 2; j++)
        {
            y[j] = b_left[j] / 2;
            y[j + N / 2] = b_right[j] / 2;
        }
    }
    else
    {
        for (int j = 0; j < N / 2; j++)
        {
            y[j] = b_left[j];
            y[j + N / 2] = b_right[j];
        }
    }
    return y;
}

QVector<double> WalshTransform::ForwardDiscreteTransform(QVector<double> sample)
{
    QVector<double> result;
    if(doAdamarToWalshShuffle)
    {
        result = hadamardToWalshShuffle(DiscreteTransform(sample, forward));
    }
    else
    {
        result = DiscreteTransform(sample, forward);
    }
    return result;
}

QVector<double> WalshTransform::BackwardDiscreteTransform(QVector<double> sample)
{
    QVector<double> result;
    if(doAdamarToWalshShuffle)
    {
        result = hadamardToWalshShuffle(DiscreteTransform(sample, backward));
    }
    else
    {
        result = DiscreteTransform(sample, backward);
    }
    return result;
}

QVector<double> WalshTransform::ForwardFastTransform(QVector<double> sample)
{
    QVector<double> result;
    if(doAdamarToWalshShuffle)
    {
        result = hadamardToWalshShuffle(FastTransform(sample, forward));
    }
    else
    {
        result = FastTransform(sample, forward);
    }
    return result;
}

QVector<double> WalshTransform::BackwardFastTransform(QVector<double> sample)
{
    QVector<double> result;
    if(doAdamarToWalshShuffle)
    {
        result = hadamardToWalshShuffle(FastTransform(sample, backward));
    }
    else
    {
        result = FastTransform(sample, backward);
    }
    return result;
}
