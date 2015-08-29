#include "ball.h"
#include <iostream>

void ball::act()
{
	if (x - radius == 0)
	{
		if (y_prev > y)
		{
			y_change =-1;
			x_change = 1;
		}
		if (y_prev == y)
		{
			std::cout << "ghf";
			y_change = 0;
			x_change = 1;
		}
		if (y_prev < y)
		{
			y_change = 1;
			x_change = 1;
		}
	}
	if (x + radius == window_size_x)
	{
		if (y_prev > y)
		{
			y_change = -1;
			x_change = -1;
		}
		if (y_prev == y)
		{
			y_change = 0;
			x_change = -1;
		}
		if (y_prev < y)
		{
			y_change = 1;
			x_change = -1;
		}
	}
	if (y + radius == window_size_y)
	{
		if (x_prev > x)
		{
			y_change = -1;
			x_change = -1;
		}
		if (x_prev == x)
		{
			y_change = -1;
			x_change = 0;
		}
		if (x_prev < x)
		{
			y_change = -1;
			x_change = 1;
		}
	}
	if (y - radius == 0)
	{
		if (x_prev > x)
		{
			y_change = 1;
			x_change = -1;
		}
		if (x_prev == x)
		{
			y_change = 1;
			x_change = 0;
		}
		if (x_prev < x)
		{
			y_change = 1;
			x_change = 1;
		}
	}
	move();
}

void ball::moveToPoint(double init_x, double init_y)
{
	double xx = init_x - x, yy = init_y - y;
	if (xx <0)
		xx *= -1;
	if (yy < 0)
		yy *= -1;
	std::cout << xx << " and " << yy << " uuu";
	double l = hypot(xx, yy);
	std::cout << l << " hyp ";
	if (!l)
		return;
	x_change = xx*(10 / l);//10 - это скорость
	y_change = yy*(10 / l);
	if (init_x < x)
		x_change *= -1;
	if (init_y < y)
		y_change *= -1;
	std::cout << x_change << " and " << y_change;
}

ball::~ball()
{
}
