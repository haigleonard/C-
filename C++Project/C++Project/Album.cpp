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
	cout << name << " total album runtime: "; d->print();
}
void Album::addSong(std::string n, int h, int m, int s)
{
	song = new Song(n, h, m , s);
	*d = *d + *song->d;
	songs.push_back(song);
	noOftracks++;
}
int Album::getTrackCount()
{
	return noOftracks;
}

std::pair<std::string, Duration> Album::longestTrack()
{
	std::string song;
	Duration *d = new Duration(0,0,0);
	for (const auto s : songs) {
		if (*d < *s->d) {
			*d = *s->d;
			song = s->getName();
		}

	}
	return std::pair <std::string, Duration>(song, *d);
}