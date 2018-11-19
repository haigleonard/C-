#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Duration.h"
class Song
{
private:
	std::string name;
public:
	Duration *d;
	Song(std::string n, int h , int m, int s) : name(n) { d = new Duration(h, m , s); };
	void print() { std::cout << "\t\t" << name << std::endl; };
	std::string getName() { return name; };
};



