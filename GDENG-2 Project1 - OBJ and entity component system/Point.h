#pragma once
class Point
{
public:
	Point();
	Point(int x, int y);
	Point(const Point& point);
	~Point();

public:
	int x = 0, y = 0;
};

