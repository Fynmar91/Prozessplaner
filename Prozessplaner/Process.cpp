#include "Process.h"

using namespace std;

Process::Process(size_t nameNr, double newEntryTime, double newDuration, size_t newPriority)
{
	setName(nameNr);
	setEntryTime(newEntryTime);
	setDuration(newDuration);
	setPriority(newPriority);
	setWaitTime(0);
}

Process::Process()
{
	
}

Process::~Process()
{

}

void Process::setName(size_t created)
{
	name = (char)('A' + created);
}

void Process::setEntryTime(double newEntryTime)
{
	if (newEntryTime >= 0)
	{
		entryTime = newEntryTime;
	}
	else
	{
		entryTime = 0;
	}
}

void Process::setDuration(double newDuration)
{
	if (newDuration >= 0)
	{
		duration = newDuration;
		setRemainingTime(newDuration);
	}
	else
	{
		duration = 0;
		setRemainingTime(0);
	}
	
}

void Process::setRemainingTime(double newRemainingTime)
{
	if (newRemainingTime >= 0)
	{
		remainingTime = newRemainingTime;
	}
	else
	{
		remainingTime = 0;
	}
	
}

void Process::setWaitTime(double newWaitTime)
{
	if (newWaitTime >= 0)
	{
		waitTime = newWaitTime;
	}
	else
	{
		waitTime = 0;
	}
}

void Process::setPriority(size_t newPriority)
{
	if (newPriority >= 0)
	{
		priority = newPriority;
	}
	else
	{
		priority = 0;
	}
}

char Process::getName()
{
	return name;
}

double Process::getEntryTime()
{
	return entryTime;
}

double Process::getDuration()
{
	return duration;
}

double Process::getRemainingTime()
{
	return remainingTime;
}

double Process::getWaitTime()
{
	return waitTime;
}

size_t Process::getPriority()
{
	return priority;
}


