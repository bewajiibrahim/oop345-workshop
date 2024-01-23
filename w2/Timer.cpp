/***********************************************************************
Student ID: 128143203
Email: iabewaji@myseneca.ca
Date of completion: 24 September 2023

I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
***********************************************************************/
#include "Timer.h"
using namespace std::chrono;
namespace sdds {
	void Timer::start()
	{
		startTime = steady_clock::now();
	}
	long long Timer::stop()
	{
		auto endTime = steady_clock::now();
		auto duration = duration_cast<nanoseconds>(endTime - startTime);
		return duration.count();
	}
}