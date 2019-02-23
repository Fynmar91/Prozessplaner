// Programmname: Prozessplaner.cpp
// Autor: Fynmar
// Datum: 2018.09.18
// Version: 1.0

#include <iostream>			//cin cout
#include <iomanip>			//setprecision
#include <vector>			//Vektoren
#include <stdlib.h>			//system("CLS") Konsole löschen
#include "Process.h"		//Klasse Process
#include <functional>
using namespace std;

const int SIM_TIME = 30;				//Länge der Simulation
const double SIM_INTERV = 0.001;		//Simulationsintervall
const int RR_ONE = 1;					//Round Robin One Zeitscheibe
const int RR_TWO = 2;					//Round Robin Two Zeitscheibe

void getProcess(vector<Process> &vector_p, size_t i);								//Prozesse lesen
void totalDuration(vector<Process> &vector_p, size_t processCount);					//Länge aller Prozesse zurückgeben
void firstComeFirstServe(vector<Process> &vector_p, size_t processCount);			//First Come First Serve Algorithmus
void shortestJobFirst(vector<Process> &vector_p, size_t processCount);				//Shortest Job First Algorithmus
void shortestRemainingTime(vector<Process> &vector_p, size_t processCount);			//Shortest Remaining Time Algorithmus
void roundRobinOne(vector<Process> &vector_p, size_t processCount);					//Round Robing mit Zeitscheibe von 1
void roundRobinTwo(vector<Process> &vector_p, size_t processCount);					//Round Robing mit Zeitscheibe von 2
void bubbleSort(vector<Process> &vector_p, size_t processCount, const function<double(int)>& func, bool lessthan);

int main()
{
	while (1)
	{
		vector<Process> processes_vector;
		size_t processes_total, algorythm;		

		cout << setprecision(4) << "Wie viele Prozesse? ";
		cin >> processes_total;
		processes_vector.reserve(processes_total);

		cout << "1: First Come First Serve" << endl << "2: Shortest Job First " << endl << "3: Shortest Remaining Time " << endl << "4: Round Robin (1)" << endl << "5: Round Robin (2)" << endl;
		cin >> algorythm;

		for (size_t i = 0; i < processes_total; i++)
		{
			cout << "Prozess eingeben (Eintrittszeit Prozessdauer Prioritaet)" << endl;
			getProcess(processes_vector, i);
		}
		system("CLS");
		cout << "Prozess\tEintrittszeit\tProzessdauer\tPrioritaet" << endl;

		for (size_t i = 0; i < processes_total; i++)
		{
			cout << processes_vector[i].getName() << "\t" << processes_vector[i].getEntryTime() << "\t\t" << processes_vector[i].getDuration() << "\t\t" << processes_vector[i].getPriority() << endl;
		}
		switch (algorythm)
		{
		case 1:
			firstComeFirstServe(processes_vector, processes_total);
			break;

		case 2:
			shortestJobFirst(processes_vector, processes_total);
			break;

		case 3:
			shortestRemainingTime(processes_vector, processes_total);
			break;

		case 4:
			roundRobinOne(processes_vector, processes_total);
			break;

		case 5:
			roundRobinTwo(processes_vector, processes_total);
			break;
		}
	}
	return 0;
}

void getProcess(vector<Process> &vector_p, size_t i)		//Prozesse lesen
{
	double entryTime;
	double duration;
	size_t priority;
	cin >> entryTime >> duration >> priority;
	vector_p.push_back(Process(i , entryTime, duration, priority));
}

void totalDuration(vector<Process> &vector_p, size_t processCount)		//Länge aller Prozesse zurückgeben
{
	double totalDuration = 0;

	for (size_t i = 0; i < processCount; i++)
	{		
		totalDuration += vector_p[i].getDuration();
	}
	cout << totalDuration << endl;
}

void bubbleSort(vector<Process> &vector_p, size_t processCount, const function<double(int)>& func, bool lessthan)
{
	Process temp_p;

	for (size_t i = 0; i < processCount - 1; i++)
	{
		for (size_t j = 0; j < processCount - 1; j++)
		{
			if (lessthan == true && func(j) > func(j + 1))
			{
				temp_p = vector_p[j];
				vector_p[j] = vector_p[j + 1];
				vector_p[j + 1] = temp_p;
			}
			else if (lessthan == false && func(j) < func(j + 1))
			{
				temp_p = vector_p[j];
				vector_p[j] = vector_p[j + 1];
				vector_p[j + 1] = temp_p;
			}
			else if (func(j) == func(j + 1) && vector_p[j].getPriority() < vector_p[j + 1].getPriority())
			{
				temp_p = vector_p[j];
				vector_p[j] = vector_p[j + 1];
				vector_p[j + 1] = temp_p;				
			}
		}
	}
}

void firstComeFirstServe(vector<Process> &vector_p, size_t processCount)		//First Come First Serve Algorithmus
{
	auto lambda = [&](int value) ->double  {return vector_p[value].getEntryTime(); };
	bubbleSort(vector_p, processCount, lambda, 1);

	cout << endl;
	for (size_t i = 0; i < processCount; i++)		//Ausgabe
	{
		cout << vector_p[i].getDuration() << " x " << vector_p[i].getName() << endl;
	}
	cout << endl;
}

void shortestJobFirst(vector<Process> &vector_p, size_t processCount)		//Shortest Job First Algorithmus
{
	auto lambda = [&](int value) ->double {return vector_p[value].getDuration(); };
	bubbleSort(vector_p, processCount, lambda, 1);

	cout << endl;
	double time = 0;
	while (time <= SIM_TIME)
	{		
		for (size_t i = 0; i < processCount; i++)
		{
			if (vector_p[i].getEntryTime() <= time && vector_p[i].getRemainingTime() > 0)		//Kontrolle der Eintrittszeit
			{
				cout << vector_p[i].getDuration() << " x " << vector_p[i].getName() << "\t" << time << " - " << time + vector_p[i].getDuration() << endl;		//Ausgabe

				vector_p[i].setRemainingTime(0);
				time = time + vector_p[i].getDuration();
				break;
			}
			if (i + 1 == processCount)		//Fortschritt der Simulationszeit
			{
				time += SIM_INTERV;
			}				
		}		
	}
	cout << endl;
}

void shortestRemainingTime(vector<Process> &vector_p, size_t processCount)		//Shortest Remaining Time Algorithmus
{
	auto lambda = [&](int value) ->double {return vector_p[value].getRemainingTime(); };
	double time = 0;
	while (time <= SIM_TIME)
	{		
		bubbleSort(vector_p, processCount, lambda, 1);
		
		char active_name = 1;
		for (size_t i = 0; i < processCount; i++)
		{
			if (vector_p[i].getEntryTime() <= time && vector_p[i].getRemainingTime() > 0)		//Kontrolle der Eintrittszeit
			{				
				if (vector_p[i].getName() != active_name)		//Prozessänderung?
				{
					if (time > 0)
					{
						cout << time << endl << vector_p[i].getName() << "\t" << time << "\t-\t";	//Ausgabe
					}
					else
					{
						cout << endl << vector_p[i].getName() << "\t" << time << "\t-\t";
					}
				}
				active_name = vector_p[i].getName();
				vector_p[i].setRemainingTime(vector_p[i].getRemainingTime() - SIM_INTERV);
				time += SIM_INTERV;
				break;		//Prozess gefunden. Zurück zum Bubble Sort
			}
			if (i + 1 == processCount)		//Fortschritt der Simulationszeit
			{
				time += SIM_INTERV;
			}
		}
	}	
	totalDuration(vector_p, processCount);
	cout << endl;
}

void roundRobinOne(vector<Process> &vector_p, size_t processCount)		//Round Robing mit Zeitscheibe von 1
{
	auto lambda = [&](int value) ->double {return vector_p[value].getWaitTime(); };
	double time = 0;
	char active_name = 1;
	while (time <= SIM_TIME)
	{			
		bubbleSort(vector_p, processCount, lambda, 0);
				
		for (size_t i = 0; i < processCount; i++)
		{
			if (vector_p[i].getEntryTime() <= time && vector_p[i].getRemainingTime() > 0)		//Kontrolle der Eintrittszeit
			{
				if (vector_p[i].getName() != active_name)		//Prozessänderung?
				{
					if (time > 0)
					{
						cout << time << endl << vector_p[i].getName() << "\t" << time << "\t-\t";		//Ausgabe
					}
					else
					{						
						cout << endl << vector_p[i].getName() << "\t" << time << "\t-\t";												
					}					
				}
				active_name = vector_p[i].getName();

				if (vector_p[i].getRemainingTime() > RR_ONE)
				{
					time += RR_ONE;
					vector_p[i].setRemainingTime(vector_p[i].getRemainingTime() - RR_ONE);
					vector_p[i].setWaitTime(0);
				}
				else
				{
					time += vector_p[i].getRemainingTime();
					vector_p[i].setRemainingTime(0);
					vector_p[i].setWaitTime(0);
				}
				for (size_t i = 0; i < processCount; i++)		//Fortschritt der Wartezeit
				{
					if (vector_p[i].getName() != active_name && vector_p[i].getEntryTime() <= time)
					{
						if (vector_p[i].getEntryTime() < time && vector_p[i].getEntryTime() > time - RR_ONE)
						{
							vector_p[i].setWaitTime(time - vector_p[i].getEntryTime());
						}
						else
						{
							vector_p[i].setWaitTime(vector_p[i].getWaitTime() + RR_ONE);
						}						
					}
				}
				break;		//Prozess gefunden. Zurück zum Bubble Sort
			}
			if (i + 1 == processCount)
			{
				for (size_t i = 0; i < processCount; i++)		//Fortschritt der Wartezeit nach Simulationsintervall
				{
					if (vector_p[i].getName() != active_name && vector_p[i].getEntryTime() <= time)
					{
						vector_p[i].setWaitTime(vector_p[i].getWaitTime() + SIM_INTERV);
					}
				}
				time += SIM_INTERV;		//Fortschritt der Simulationszeit
			}
		}
	}
	totalDuration(vector_p, processCount);
}

void roundRobinTwo(vector<Process> &vector_p, size_t processCount)		//Round Robing mit Zeitscheibe von 2
{	
	auto lambda = [&](int value) ->double {return vector_p[value].getWaitTime(); };
	double time = 0;
	char active_name = 1;
	while (time <= SIM_TIME)
	{		
		bubbleSort(vector_p, processCount, lambda, 0);
				
		for (size_t i = 0; i < processCount; i++)
		{
			if (vector_p[i].getEntryTime() <= time && vector_p[i].getRemainingTime() > 0)		//Kontrolle der Eintrittszeit
			{
				if (vector_p[i].getName() != active_name)		//Prozessänderung?
				{
					if (time > 0)
					{
						cout << time << endl << vector_p[i].getName() << "\t" << time << "\t-\t";		//Ausgabe
					}
					else
					{
						cout << endl << vector_p[i].getName() << "\t" << time << "\t-\t";
					}
				}
				active_name = vector_p[i].getName();

				if (vector_p[i].getRemainingTime() > RR_TWO)
				{
					time += RR_TWO;
					vector_p[i].setRemainingTime(vector_p[i].getRemainingTime() - RR_TWO);
					vector_p[i].setWaitTime(0);					
				}
				else
				{
					time += vector_p[i].getRemainingTime();
					vector_p[i].setRemainingTime(0);
					vector_p[i].setWaitTime(0);					
				}
				for (size_t i = 0; i < processCount; i++)		//Fortschritt der Wartezeit
				{
					if (vector_p[i].getName() != active_name && vector_p[i].getEntryTime() <= time)
					{
						if (vector_p[i].getEntryTime() < time && vector_p[i].getEntryTime() > time - RR_TWO)
						{
							vector_p[i].setWaitTime(time - vector_p[i].getEntryTime());
						}
						else
						{
							vector_p[i].setWaitTime(vector_p[i].getWaitTime() + RR_TWO);
						}
					}
				}
				break;		//Prozess gefunden. Zurück zum Bubble Sort
			}
			if (i + 1 == processCount)
			{
				for (size_t i = 0; i < processCount; i++)		//Fortschritt der Wartezeit nach Simulationsintervall
				{
					if (vector_p[i].getName() != active_name && vector_p[i].getEntryTime() <= time)
					{
						vector_p[i].setWaitTime(vector_p[i].getWaitTime() + SIM_INTERV);
					}
				}
				time += SIM_INTERV;		//Fortschritt der Simulationszeit
			}
		}
	}
	totalDuration(vector_p, processCount);
}