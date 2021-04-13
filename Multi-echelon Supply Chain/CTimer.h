#pragma once
#include "Windows.h"

class CTimer
{
public:
	CTimer();
	~CTimer();

	void vStart(double dDurationInSeconds);
	int iTimeisOver();
private:
	double dDuration;
	double dSeconds;
	LARGE_INTEGER li_start, li_end, li_freq;
};

