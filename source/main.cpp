#include <stdio.h>
#include <functional>

#include "gfx.h"
#include "input.h"

#include "pongpaddle.h"

#ifdef __MACOSX__
bool aptMainLoop()
{
	return true;
}
#else

#include <3ds.h>

#endif


class Ball
{
public:
	Ball(Gfx &graphics) : gfx(graphics)
	{

	}

	~Ball()
	{

	}

	void setX(float xVal)
	{
		x = xVal;
	}

	void setY(float yVal)
	{
		y = yVal;
	}

	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	void update()
	{
		x += xspeed;
		if (x > 380)
		{
			x = 380;
			flipXSpeed();
		}
		else if(x < 0)
		{
			x = 0;
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

	void flipYSpeed()
	{
		yspeed *= -1.0f;
	}

	void flipXSpeed()
	{
		xspeed *= -1.0f;
	}

	void draw()
	{
		gfx.drawRectangle(x, y, 20, 20, Colour(0xff, 0xff, 0xff, 0xff));
	}

private:
	float xspeed { 2.5f };
	float yspeed { 2.5f };
	int y { 80 };
	int x { 80 };
	Gfx &gfx;
};

class CollisionHandler
{
public:
	CollisionHandler(PongPaddle &paddle, Ball &targetBall) : pongPaddle(paddle), ball(targetBall) {}

	~CollisionHandler() {}

	void checkCollision()
	{
		// Colliding with right side of paddle
		bool collidingRight = pointInRange(pongPaddle.getX()+20, ball.getX(), ball.getX()+20) && (pointInRange(ball.getY(), pongPaddle.getY(), pongPaddle.getY()+80) || pointInRange(ball.getY()+20, pongPaddle.getY(), pongPaddle.getY()+80));
		bool collidingUnder = pointInRange(pongPaddle.getY()+80, ball.getY(), ball.getY()+20) && (pointInRange(ball.getX(), pongPaddle.getX(), pongPaddle.getX()+20) || pointInRange(ball.getX()+20, pongPaddle.getX(), pongPaddle.getX()+20));
		bool collidingTop 	= pointInRange(pongPaddle.getY(), ball.getY(), ball.getY()+20) && (pointInRange(ball.getX(), pongPaddle.getX(), pongPaddle.getX()+20) || pointInRange(ball.getX()+20, pongPaddle.getX(), pongPaddle.getX()+20));

		if (collidingRight)
		{
			ball.flipXSpeed();
			ball.setX(pongPaddle.getX()+20);
		}
		else if (collidingUnder)
		{
			ball.flipYSpeed();
			ball.setY(pongPaddle.getY()+80);
		} 
		else if (collidingTop)
		{
			ball.flipYSpeed();
			ball.setY(pongPaddle.getY()-20);
		}
	}

	bool pointInRange(int point, int rangeStart, int rangeEnd)
	{
		return point >= rangeStart && point <= rangeEnd;
	}
private:
	PongPaddle &pongPaddle;
	Ball &ball;
};

int main(int argc, char **argv)
{
	Gfx gfx;
	Input input;

	PongPaddle paddle(gfx, input);
	Ball ball(gfx);
	CollisionHandler collisionHandler(paddle, ball);

	// Main loop
	while (aptMainLoop() && !input.startDown())
	{
		input.scan();
		
		paddle.update();
		ball.update();

		collisionHandler.checkCollision();

		gfx.renderOnTop([&]{
			ball.draw();
			paddle.draw();	
		});

		gfx.flip();
	}
	
	return 0;
}
