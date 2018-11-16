#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Song.h"
#include "Duration.h"
class Album
{
private:
	std::string name;
	Song *song;
	Duration d;
	std::vector <Song*> songs;
public:
	Album(std::string n) : name(n) {};
	~Album();
	std::string getName() { return name; };
	void print();
	void addSong(std::string, int, int, int);
};

