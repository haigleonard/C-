// C++Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Artist.h"
using namespace std;
string line;
Artist *artist;
vector <Artist*> Artists;

int main()
{
	
	std::ifstream myfile("albums.txt");
	
	string artistTemp;
	string albumTemp;
	while (std::getline(myfile, line))
	{
		
		stringstream ss(line);
		string strNumber1;
		std::getline(ss, strNumber1, ':');
		

		if (strNumber1 == "0") {
			int h, m, s;
			string n;
			h = atoi(strNumber1.c_str());

			std::getline(ss, strNumber1, ':');
			m = atoi(strNumber1.c_str());

			std::getline(ss, strNumber1, '-');
			s = atoi(strNumber1.c_str());

			std::getline(ss, strNumber1, ' ');
			std::getline(ss, strNumber1, '\n');
			n = strNumber1;
			auto it = std::find_if(Artists.begin(), Artists.end(), [&artistTemp](Artist* obj) {return obj->getName() == artistTemp; });
			if (it != Artists.end())
			{
				auto index = std::distance(Artists.begin(), it);
				Artists.at(index)->addSong(albumTemp, n, h, m, s);
			}
		}
		else {
			string strNumber2;
			std::getline(ss, strNumber2, '\n');
			auto it = std::find_if(Artists.begin(), Artists.end(), [&strNumber1](Artist* obj) {return obj->getName() == strNumber1; });
				
				if (it != Artists.end())
				{
					auto index = std::distance(Artists.begin(), it);
					Artists.at(index)->addAlbum(strNumber2);
					artistTemp = strNumber1; albumTemp = strNumber2;
				}
				else {
					artist = new Artist(strNumber1);
					artist->addAlbum(strNumber2);
					Artists.push_back(artist);
					artistTemp = strNumber1; albumTemp = strNumber2;
				}
		}
	}
	for (const auto a : Artists)
		a->print();
	
	int greatest = 0;
	std::string albumName;
	for (int i = 0; i < Artists.size(); i++) {
		if (Artists.at(i)->getLongestAlbum().second > greatest)
		{
			greatest = Artists.at(i)->getLongestAlbum().second;
			albumName = Artists.at(i)->getLongestAlbum().first;
		}
	}
	cout << albumName << ": "<< greatest << endl;
	
	std::sort(Artists.begin(), Artists.end(), [](const Artist *lhs, const Artist *rhs) { return *lhs < *rhs; });

	for (const auto a : Artists)
		cout << a->name << endl;

	int seconds = 0;
	std::string song;
	for (const auto a : Artists) {
		if (a->longestTrack().second > seconds) {
			seconds = a->longestTrack().second;
			song = a->longestTrack().first;
		}
	}
	cout << seconds << ":" << song << endl;
}


