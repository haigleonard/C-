#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "Album.h"

class Artist
{
private:
	
	
	Album *album;
	std::vector <Album*> albums;
	//Durations *d;
public:
	Artist(std::string  n) : name(n) {};
	~Artist();
	std::string name;
	Duration *d = new Duration(0, 0, 0);
	void print();
	std::string getName() { return  name; };
	void addAlbum(std::string n);
	void addSong(std::string, std::string, int, int, int);
	std::pair<std::string, int> getLongestAlbum();
	bool operator<(const Artist& p) const
	{
		return name < p.name; // order by name
	}
};