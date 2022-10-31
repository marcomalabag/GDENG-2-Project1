#include "Point.h"

Point::Point()
{
	this->x = 0;
	this->y = 0;
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point& point)
{
	this->x = point.x;
	this->y = point.y;
}

Point::~Point()
{
}
