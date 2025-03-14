
#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>
#include <vector>
#include <map> 
#include <set>
#include <functional>
using namespace std;
class dataBase2
{
	class IDandAction;
public:
	string webSite;
	std::vector<IDandAction> Action;

	dataBase2(string w)
	{
		webSite = w;
	}

	string getWebsite()
	{
		return webSite;
	}

	bool newID(string id, string action)
	{
		for (std::vector<IDandAction>::iterator it = Action.begin(); it != Action.end(); ++it) {
			if (!it->getID().compare(id))
			{
				it->addAction(action);
				return true;
			}
		}
		dataBase2::IDandAction *ia = new IDandAction();
		ia->setID(id);
		ia->addAction(action);
		Action.push_back(*ia);
		return false;
	}
	void getActions(std::map<string, int> &myMap)
	{
		for (std::vector<IDandAction>::iterator it = Action.begin(); it != Action.end(); ++it) {
			for (int z = 0; z < it->Action.size(); z++) {
				map <string, int> ::iterator itr = myMap.find(it->Action[z]);

				if (itr != myMap.end())
				{
					int temp = itr->second;
					myMap.erase(it->Action[z]);
					myMap.insert(pair <string, int>(it->Action[z], temp += 1));
				}
				else {
					myMap.insert(pair <string, int>(it->Action[z], 1));
				}
			}
		}
	}
	int actionCount()
	{
		int count = 0;
		for (std::vector<IDandAction>::iterator it = Action.begin(); it != Action.end(); ++it) {
			count += it->Action.size();
		}
		return count;
	}

	class IDandAction
	{
	public:
		string ID;
		std::vector<std::string> Action;
		void setID(string id)
		{
			ID = id;
		}
		void addAction(string a)
		{
			Action.push_back(a);
		}
		string getID()
		{
			return ID;
		}
	};
};

class Statistics
{

public:

	void totalactions(vector<dataBase2> &DataB)
	{
		for (std::vector<dataBase2>::iterator it = DataB.begin(); it != DataB.end(); ++it) {
			cout << it->getWebsite() << " :: " << it->actionCount() << endl;
		}
	}

	void topactions(vector<dataBase2> &DataB)
	{
		std::map<string, int> myMap;
		for (std::vector<dataBase2>::iterator it = DataB.begin(); it != DataB.end(); ++it) {
			it->getActions(myMap);
		}
		for (map<string, int>::const_iterator it = myMap.begin(); it != myMap.end(); ++it)
		{
			std::cout << it->first << " " << it->second << "\n";
		}
	}
	void meansessionactions(vector<dataBase2> &DataB)
	{
		for (std::vector<dataBase2>::iterator it2 = DataB.begin(); it2 != DataB.end(); ++it2) {
			cout << it2->getWebsite() << " :: " << (float)it2->actionCount() / it2->Action.size() << endl;
		}
	}

};


void io(vector<dataBase2> &DataB) {
	ifstream inFile;
	inFile.open("TestInput.txt");
	if (!inFile) {
		cerr << "Unable to open file TestInput.txt";
		exit(1);   // call system to stop
	}
	string x;
	while (std::getline(inFile, x)) {
		std::vector<std::string> result;
		std::istringstream iss(x);
		for (std::string x; iss >> x; )
			result.push_back(x);

		bool lock = false;
		int size = DataB.size();
		for (int i = 0; i < size; i++) {
			if (!DataB[i].getWebsite().compare(result[1]))
			{
				DataB[i].newID(result[0], result[2]);
				lock = true;
			}
		}
		if (!lock) {
			dataBase2 *db = new dataBase2(result[1]);
			db->newID(result[0], result[2]);
			DataB.push_back(*db);
		}
	}
	inFile.close();
}

int main()
{
	vector<dataBase2> DataB;
	io(DataB);

	Statistics stat;
	cout << "Total number of actions per website:" << endl;
	stat.totalactions(DataB);
	cout << "20 most frequent actions:" << endl;
	stat.topactions(DataB);
	cout << "Mean number of actions in a session per website:" << endl;
	stat.meansessionactions(DataB);

	return 0;
}

