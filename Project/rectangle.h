//rectangle class from: http://www.danielsoltyka.com/programming/2010/05/30/c-vector2d-rectangle-classes/

#ifndef _RECTANGLE_H
#define _RECTANGLE_H
#pragma once

#include "vector2D.h"

class Rectangle
{
public:
	Rectangle(int x = 0, int y = 0, int w = 0, int h = 0);
	~Rectangle(void) {};

	inline int Left(void) const { return x; }
	inline int Right(void) const { return x + w; }
	inline int Top(void) const { return y; }
	inline int Bottom(void) const { return y + h; }

	bool Contains(Vector2D& vVec) const;
	bool Contains(int x, int y) const;

	static Rectangle Empty();

	// Static methods below are derived from the RectangleExtensions class
	// written in C#, released under the MSPL
	static Vector2D GetIntersectionDepth(const Rectangle& rectA, const Rectangle& rectB);
	static Vector2D GetBottomCenter(const Rectangle& rect);
	static Vector2D GetCenter(const Rectangle& rect);
	static float GetDistance(const Rectangle& rectA, const Rectangle& rectB);
	static Vector2D GetDirection(const Rectangle& rectA, const Rectangle& rectB);

	Rectangle& operator= (const Rectangle& r2);

	bool operator== (const Rectangle& r2) const;
	bool operator!= (const Rectangle& r2) const;

public:
	int x, y, w, h;
};

#endif

