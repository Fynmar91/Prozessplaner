#pragma once
class Process
{
private:

	char name;
	double entryTime;
	double duration;
	double remainingTime;
	double waitTime;
	size_t priority;

	void setName(size_t created);

public:	

	Process(size_t nameNr, double newEntryTime, double newDuration, size_t newPriority);
	Process();
	~Process();

	void setEntryTime(double newEntryTime);
	void setDuration(double newDuration);
	void setRemainingTime(double newRemainingTime);
	void setWaitTime(double newWaitTime);
	void setPriority(size_t newPriority);

	char getName();
	double getEntryTime();
	double getDuration();
	double getRemainingTime();
	double getWaitTime();
	size_t getPriority();
};

