#pragma once
#ifndef SHAPES_H
#define SHAPES_H

#include "Point.h"
#include <vector>

enum ShapeType
{
	LINE,
	BEZIER,
	ARC
};

class Shape
{
protected:
	Point p1, p2;
	ShapeType type;

public:
	virtual ~Shape() {}
	Shape() : p1(), p2() {}
	Shape(const Point _p1, const Point _p2) { p1 = _p1; p2 = _p2; }

	virtual std::vector<Point> getCoordinates()= 0;

	void setfirstPoint(const Point _p1) { p1= _p1; }
	void setSecondPoint(const Point _p2) { p2= _p2; }

	Point& getFirstPoint() { return p1; } 
	Point& getSecondPoint() { return p2; }
};
#endif // !SHAPES_H
