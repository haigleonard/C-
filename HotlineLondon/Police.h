#pragma once
#include "math.h"
#include <time.h>
#include <stdlib.h>
class Police
{
public:
	Police();
	~Police();
	const double PI = 3.1415926535897932384626433832795;
	float x = 0;
	float y = 0;
	bool siren = true;
	int sirenCount = 0;
	float Vtri = 0;
	float a = 0;
	bool crossRoad = false;
	int crossCount = 0;
	void updateCar()
	{
		x += Vtri * cos((90 + a)*(PI / 180.0));
		y += Vtri * sin((90 + a)*(PI / 180.0));
		if (sirenCount > 20 && siren) {
			siren = false;
		}
		else if (sirenCount > 40) {
			siren = true; sirenCount = 0;
		}
		sirenCount++;
		if (crossRoad) {
			crossCount++;
		}
		if (crossCount > 40) {
			crossRoad = false;
		}
	}
	void accelerate()
	{
		if (Vtri < 0.25) {
			Vtri += 0.001;
		}
	}
	void brake()
	{
		if (Vtri > 0) {
			Vtri -= 0.01;
		}
	}
	void pedalOff()
	{
		if (Vtri > 0) {
			Vtri -= 0.001;
		}
	}
	void reverse()
	{
		Vtri -= 0.001;
	}
	void left()
	{
		a += 90;
	}
	void right()
	{
		a -= 90;
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}
	float getA()
	{
		return a;
	}
	void turn()
	{
		if (!crossRoad) {
			srand(time(NULL));
			int R = rand() % 2;

			x -= Vtri * cos((90 + a)*(PI / 180.0));
			y -= Vtri * sin((90 + a)*(PI / 180.0));
			if (R == 1)
			{
				left();
			}
			else {
				right();
			}
		}
	}
};

