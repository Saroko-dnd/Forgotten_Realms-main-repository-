#pragma once

#include "GLOBALS/GLOBAL_VARIABLES.h"
#include "thing.h"
#include <cmath>
#include <iostream>

class ball:public thing
{
public:
	int radius;
	int x_prev;
	int y_prev;
	int x_change;
	int y_change;

	//исправленный метод движения в точку
	void moveToPoint(double init_x, double init_y);

	void move()
	{
		x_prev = x;
		y_prev = y;
		x += x_change;
		y += y_change;
	}
	void act();
	ball(int x_new, int y_new, int new_rad, int v_x, int v_y) :thing(x_new, y_new), radius(new_rad), x_change(v_x), y_change(v_y)
	{};
	~ball();
};

