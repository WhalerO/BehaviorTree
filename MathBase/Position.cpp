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