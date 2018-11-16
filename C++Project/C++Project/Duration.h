#pragma once
#include <string>
#include <iostream>
using namespace std;
class Duration
{
private:
	int hours = 0, minutes = 0, seconds = 0;
public:
	void add(int h, int m, int s) { hours += h; minutes += m; seconds += s; }
	void print() {std::cout << hours << ":" << minutes << ":" << seconds << ":" << std::endl;}
};


