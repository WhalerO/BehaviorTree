#pragma once

#include "_MathBase.h"

//==============================================================================
class Position
{
public:
	Position();
	Position(float x, float y);

	float xPos, yPos;

	void setPosition(int x, int y);
	float norm() { return sqrt(xPos * xPos + yPos * yPos); }

	bool inRange(Position target, float range = EPS);
	void transToPosition(Position target, float timeStep, float speed);
};
//-------------------------------------------------------------------------
inline Position operator-(Position p1, Position p2)
{ return Position(p1.xPos - p2.xPos, p1.yPos - p2.yPos); }
inline Position operator+(Position p1, Position p2)
{ return Position(p1.xPos + p2.xPos, p1.yPos + p2.yPos); }
inline Position operator*(Position p1, float p2)
{ return Position(p1.xPos * p2, p1.yPos * p2); }
inline Position operator*(float p1, Position p2)
{ return Position(p1 * p2.xPos, p1 * p2.yPos); }
inline Position operator/(Position p1, float p2)
{ return Position(p1.xPos / p2, p1.yPos / p2); }
inline float operator* (Position p1, Position p2)
{ return p1.xPos * p2.xPos + p1.yPos * p2.yPos; }