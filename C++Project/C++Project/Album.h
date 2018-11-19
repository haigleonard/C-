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
	int noOftracks = 0;
	Song *song;
	
	std::vector <Song*> songs;
public:
	Album(std::string n) : name(n) {};
	~Album();
	Duration *d = new Duration(0, 0, 0);
	std::string getName() { return name; };
	void print();
	void addSong(std::string, int, int, int);
	int getTrackCount();
	Song lastSong() { return *songs.at(songs.size()-1); };
};

