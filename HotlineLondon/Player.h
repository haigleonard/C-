#pragma once
#include "math.h"
const double PI = 3.1415926535897932384626433832795;
class Player
{
public:
	float vertOriginal[8] = { -2, -2, -2, 2, 2, 2, 2, -2 };
	float x = 0;
	float y = 0;
	float Vtri = 0;
	float a = 0;
	float zoom = 15;
	Player();
	~Player();
	void updateCar()
	{
		x += Vtri * cos((90 + a)*(PI / 180.0));
		y += Vtri * sin((90 + a)*(PI / 180.0));
		zoom = 100 + Vtri*10;
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
		a+= (Vtri * 10);
	}
	void right()
	{
		a-= (Vtri * 10);
	}
};

