#pragma once
class thing
{
public:
	int x;
	int y;
	virtual void act()=0;
	thing(int new_x, int new_y) :x(new_x), y(new_y)
	{};
	virtual ~thing(){};
};

