#pragma once

class Point
{
public:
	Point()
	{
	}
	Point(int _x, int _y) : x(_x), y(_y)
	{
	}

	Point& operator=(const Point& pt)
	{
		x = pt.x;
		y = pt.y;
		return *this;
	}
	Point operator+(const Point& pt)
	{
		return Point(pt.x + x, pt.y + y);
	}
	Point operator*(int i)
	{
		return Point(x * i, y * i);
	}

public:
	int x;
	int y;
};


static bool operator==(const Point& lhs, const Point& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
static bool operator!=(const Point& lhs, const Point& rhs)
{
	return lhs.x != rhs.x || lhs.y != rhs.y;
}