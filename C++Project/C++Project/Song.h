#pragma once
#include <string>
#include <vector>
#include <iostream>
class Song
{
private:
	std::string name;
public:
	Song(std::string n) : name(n) {};
	~Song();
	void print();
};



