#include "pongpaddle.h"

PongPaddle::PongPaddle(Gfx &graphics, Input &inputHandler) : gfx(graphics), input(inputHandler) {}

PongPaddle::~PongPaddle() {}

int PongPaddle::getX()
{
	return x;
}

int PongPaddle::getY()
{
	return y;
}

void PongPaddle::update()
{
	y += input.circleYAxis() * 3.0f;

	if (y > 240-80)
	{
		y = 240 - 80;
	}
	else if (y < 0)
	{
		y = 0;
	}
}

void PongPaddle::draw()
{
	gfx.drawRectangle(x, y, 20, 80, Colour(0xff, 0xff, 0xff, 0xff));
}