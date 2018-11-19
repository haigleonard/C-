#pragma once
#include <string>
#include <iostream>
using namespace std;
class Duration
{
private:
	int hours = 0, minutes = 0, seconds = 0;
public:
	Duration(int h, int m, int s) : hours(h), minutes(m), seconds(s){};
	void print() {std::cout << hours << ":" << minutes << ":" << seconds << std::endl;}
	int getHour() { return hours; }
	int getMinute() { return minutes; }
	int getSecond() { return seconds; }
	int getLength() { return (60 * 60 * hours) + (60 * minutes) + seconds; }
	Duration operator+(Duration &d)
	{
		Duration dd(hours, minutes, seconds);
		dd.hours += d.hours;
		dd.minutes += d.minutes;
		dd.seconds += d.seconds;
		return dd;
	}
	bool operator<(Duration &d)
	{
		return getLength() < d.getLength();
	}
};


