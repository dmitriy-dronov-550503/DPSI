#pragma once
#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

class TimeRdtsc {
private:
    long long startTime, endTime;
public:
    void start() {
        __asm("xor %eax, %eax");
        __asm("cpuid");
        //startTime = __rdtsc();
    }

    void stop() {
        __asm("xor %eax, %eax");
        __asm("cpuid");
        //endTime = __rdtsc();
    }

    long long getResult() {
        return endTime - startTime;
    }
};

class TimeChrono {
public:
   time_point<high_resolution_clock, high_resolution_clock::duration> startTime;
   time_point<high_resolution_clock, high_resolution_clock::duration> endTime;

    void start() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        endTime = std::chrono::high_resolution_clock::now();
    }

    long long getResult() {
        return duration_cast<nanoseconds>(endTime - startTime).count();
    }
};

#ifdef _WIN32
class TimeQueryPerformance {
public:
	double PCFreq = 0.0;
    long long startTime = 0;
	LARGE_INTEGER li;

	void start() {
		//LARGE_INTEGER li;
		if (!QueryPerformanceFrequency(&li))
			cout << "QueryPerformanceFrequency failed!\n";

		PCFreq = double(li.QuadPart) / 1000000000.0;;

		QueryPerformanceCounter(&li);
		startTime = li.QuadPart;
	}

	void stop() {
		QueryPerformanceCounter(&li);
	}

	double getResult() {
		return double(li.QuadPart - startTime) / PCFreq;
	}

};
#endif
