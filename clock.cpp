#include "clock.h"

using namespace RN;

Clock::Clock()
{
		Reset();
}

double Clock::Now()
{
		_t2 = high_resolution_clock::now();
			return duration_cast<duration<double>>(_t2 - _t1).count();
}

void Clock::Reset()
{
		_t1 = high_resolution_clock::now();
}

double Clock::Total()
{
		return duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
}
