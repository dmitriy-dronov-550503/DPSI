#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Matrix {

private:
    T fillPosition;

public:
    T** ptr;
    int m, n;

    Matrix(int inM, int inN, bool needFill = false) {
        m = inM;
        n = inN;
        ptr = (T**)malloc(m * sizeof(T));
        if (ptr == nullptr) throw "Memory allocation failed.";
        for (int i = 0; i < m; i++) {
            *(ptr + i) = (T*)malloc(n * sizeof(T));
            if (*(ptr + i) == nullptr) throw "Memory allocation failed.";
        }
        if(needFill)
        {
            fill(0);
        }
        else
        {
            fillZero();
        }
	}

    T** getPointer() {
        return ptr;
	}

	int getLastGeneratedNumber() {
		return fillPosition;
	}

    void fill(T fillPosition) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ptr[i][j] = fillPosition++;
			}
		}
	}

    void fillZero() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ptr[i][j] = 0;
            }
        }
    }

	void fillRandom() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                ptr[i][j] = (T)(rand() % 100);
			}
		}
	}



	~Matrix() {
        for (int i = 0; i < m; i++) {
            free(*(ptr + i));
		}
        free(ptr);
	}
};
