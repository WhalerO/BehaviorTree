#include "Position.h"

//==============================================================================
Position::Position()
{
}
Position::Position(float x, float y)
{
	xPos = x;
	yPos = y;
}
//==============================================================================
void Position::setPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}
//==============================================================================
void Position::transToPosition(Position target, float timeStep, float speed)
{
	Position dir = target - *this;
	float range = dir.norm();
	dir = dir / range;
	
	if(range < speed * timeStep){
		*this = target;
		return;
	}
	else{
		*this = *this + dir * speed * timeStep;
		return;
	}
}
//==============================================================================
bool Position::inRange(Position target, float range)
{
	Position dir = target - *this;
	if(dir.norm() < range)
		return true;
	else
		return false;
}