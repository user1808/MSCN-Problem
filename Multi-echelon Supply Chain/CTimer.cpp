#include "pch.h"
#include "CTimer.h"


CTimer::CTimer()
{
	dSeconds = 0;
	QueryPerformanceFrequency(&li_freq);
}


CTimer::~CTimer()
{
}

void CTimer::vStart(double dDurationInSeconds)
{
	dDuration = dDurationInSeconds;
	QueryPerformanceCounter(&li_start);
}

int CTimer::iTimeisOver()
{
	QueryPerformanceCounter(&li_end);
	dSeconds = li_end.QuadPart - li_start.QuadPart;
	dSeconds = dSeconds / li_freq.QuadPart;

	if (dDuration - dSeconds < 0)
		return 0;
	else
		return dDuration - dSeconds;
}
