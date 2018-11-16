#include "pch.h"
#include "Album.h"


Album::~Album()
{
}
void Album::print()
{
	std::cout << "\t" << name << std::endl;
	for (int i = 0; i < songs.size(); i++) {
		songs.at(i)->print();
	}
	cout << name << " total album runtime: "; d.print();
}
void Album::addSong(std::string n, int h, int m, int s)
{
	song = new Song(n);
	songs.push_back(song);
	d.add(h,m,s);
}
