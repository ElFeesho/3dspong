#include <3ds.h>
#include <sf2d.h>
#include <stdio.h>
#include <functional>

#include "gfx.h"
#include "input.h"

class PongPaddle
{
public:
	PongPaddle(Gfx &graphics, Input &inputHandler) : gfx(graphics), input(inputHandler)
	{

	}

	~PongPaddle()
	{

	}

	void update()
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

	void draw()
	{
		gfx.renderOnTop([&]{
			gfx.drawRectangle(20, y, 20, 80, Colour(0xff, 0xff, 0xff, 0xff));
		});
	}

private:
	int y { 60 };
	Gfx &gfx;
	Input &input;
};

int main(int argc, char **argv)
{
	Gfx gfx;
	Input input;

	PongPaddle paddle(gfx, input);

	// Main loop
	while (aptMainLoop() && !input.startDown())
	{
		input.scan();
		
		paddle.update();
		paddle.draw();

		gfx.flip();
	}
	
	return 0;
}
