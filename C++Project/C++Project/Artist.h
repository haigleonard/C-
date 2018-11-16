#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Album.h"

class Artist
{
private:
	std::string name;
	Duration d;
	Album *album;
	std::vector <Album*> albums;
	//Durations *d;
public:
	Artist(std::string  n) : name(n) {};
	~Artist();
	void print();
	std::string getName() { return  name; };
	void addAlbum(std::string n);
	void addSong(std::string, std::string, int, int, int);
};