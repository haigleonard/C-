
#ifndef OBB_H
#define OBB_H
#include <string>

const int NUMVERTS = 4;

class Point
{
public:
	float x;
	float y;
	
};

class OBB
{
	
public:
	std::string idString;
	OBB();
	void setID(std::string);
	Point vert[NUMVERTS];
	Point vertOriginal[NUMVERTS];
	void drawOBB();
	void transformPoints(float matrix[16]);
	bool SAT2D(OBB& p2);
	bool SATtest(float proj[4], float len);
};

#endif