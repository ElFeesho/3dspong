#include "ball.h"

#include "gfx.h"

Ball::Ball(Gfx &graphics) : gfx(graphics)
{

}

Ball::~Ball()
{

}

void Ball::setX(float xVal)
{
	x = xVal;
}

void Ball::setY(float yVal)
{
	y = yVal;
}

int Ball::getX()
{
	return x;
}

int Ball::getY()
{
	return y;
}

void Ball::update()
{
	x += xspeed;
	if (x > 380)
	{
		x = 380;
		flipXSpeed();
	}
	else if(x < -100)
	{
		x = 160;
		flipXSpeed();
	}
	
	y += yspeed;
	if (y > 220)
	{
		y = 220;
		flipYSpeed();
	}
	else if(y < 0)
	{
		y = 0;
		flipYSpeed();
	}
}

void Ball::flipYSpeed()
{
	yspeed *= -1.0f;
}

void Ball::flipXSpeed()
{
	xspeed *= -1.0f;
}

void Ball::draw()
{
	gfx.drawRectangle(x, y, 20, 20, Colour(0xff, 0xff, 0xff, 0xff));
}