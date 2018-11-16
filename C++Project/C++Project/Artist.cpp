#include "pch.h"
#include "Artist.h"
void Artist::print()
{
	std::cout << name << std::endl;
	for (int i = 0; i < albums.size(); i++) {
		albums.at(i)->print();
	}
	cout << name << " total artist runtime: "; d.print();
}


void Artist::addAlbum(std::string n)
{
	album = new Album(n);
	albums.push_back(album);
}


void Artist::addSong(std::string a, std::string n, int h, int m, int s)
{
	auto it = std::find_if(albums.begin(), albums.end(), [&a](Album* obj) {return obj->getName() == a; });
	if (it != albums.end())
	{
		auto index = std::distance(albums.begin(), it);
		albums.at(index)->addSong(n, h, m, s);
	}
	d.add(h, m, s);
}