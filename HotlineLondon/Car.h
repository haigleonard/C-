#pragma once
#include "math.h"

#include <time.h>
#include <stdlib.h>
class Car
{

public:
	float x = 7.5;
	float y = 7.5;
	float Vtri = 0;
	float a = 0;
	double PI = 3.1415926535897932384626433832795;
	float zoom = 15;
	float width = -0.4;
	float height = -0.4;
	void updateCar()
	{
		x += Vtri * cos((90 + a)*(PI / 180.0));
		y += Vtri * sin((90 + a)*(PI / 180.0));
		zoom = 15 + Vtri * 10;
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
	void stop()
	{
		x -= (Vtri*2) * cos((90 + a)*(PI / 180.0));
		y -= (Vtri*2) * sin((90 + a)*(PI / 180.0));
		Vtri = 0;
	}
};

	class PlayerCar: public Car
	{
	public:
		float vertOriginal[8] = { -0.75, -1.5, -0.75, 1.5, 0.75, 1.5, 0.75, -1.5 };
		void left()
		{
			a += (Vtri * 10);
		}
		void right()
		{
			a -= (Vtri * 10);
		}
		void setLoc() { x = 7.5; y = 7.5;}
	};
	class PoliceCar : public Car
	{
	public:
		float vertOriginal[8] = { -0.5, 0.5, -0.5, 1.5, 0.5, 1.5, 0.5, 0.5 };
		float vertOriginalb[8] = { -0.5, -1.5, -0.5, -0.5, 0.5, -0.5, 0.5, -1.5 };
		bool siren = true;
		int sirenCount = 0;
		bool crossRoad = false;
		int crossCount = 0;
		void updateSiren()
		{
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
		void left()
		{
			a += 90;
		}
		void right()
		{
			a -= 90;
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
		void setLoc() { x = 0; y = 0; }
		
	};

