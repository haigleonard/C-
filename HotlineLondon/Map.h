#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;
class Map
{
public:
	int mapCoor[30][30];
	int random[2];
	vector<int>roadX;
	vector<int>roadY;
	Map() {
		ifstream inFile;
		inFile.open("map.txt");
		if (!inFile) {
			cerr << "Unable to open file TestInput.txt";
			exit(1);   // call system to stop
		}
		string x;
		int col = 0;
		
		while (std::getline(inFile, x)) {
			std::vector<std::string> result;
			std::istringstream iss(x);
			for (std::string x; iss >> x; )
				result.push_back(x);
			int row = 0;
			for (std::vector<string>::iterator it = result.begin(); it != result.end(); ++it) {
				stringstream coor(*it);
				int x = 0;
				coor >> x;
				mapCoor[row][col] = x;
				if (x == 2 || x == 3) {
					roadX.push_back(row);
					roadY.push_back(col);
				}
				row++;
			}
			col++;
		}
		inFile.close();
	};
	~Map();
	void randomPos()
	{
		srand(time(NULL));
		int R = rand() % roadX.size();
		random[0] = roadX.at(R);
		random[1] = roadX.at(R);
	}
};

