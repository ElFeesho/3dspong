#pragma once

#include "gfx.h"
#include "input.h"

class PongPaddle
{
public:
	PongPaddle(Gfx &graphics, Input &inputHandler);
	~PongPaddle();

	int getX();

	int getY();

	void update();

	void draw();

private:
	int x { 20 };
	int y { 80 };
	Gfx &gfx;
	Input &input;
};