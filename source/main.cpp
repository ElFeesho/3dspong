#include <stdio.h>
#include <functional>

#include "gfx.h"


#include "pongpaddle.h"
#include "ball.h"

#ifdef __MACOSX__
#	include "sfmlinput.h"
#	include "sfmlgfx.h"

bool aptMainLoop()
{
	return true;
}

#else
#	include <3ds.h>
#	include "HIDInput.h"
#	include "sf2dgfx.h"
#endif

class CollisionHandler
{
public:
	CollisionHandler(PongPaddle &paddle, Ball &targetBall) : pongPaddle(paddle), ball(targetBall) {}

	~CollisionHandler() {}

	bool checkCollision()
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

		return collidingTop || collidingRight || collidingUnder;
	}

	bool pointInRange(int point, int rangeStart, int rangeEnd)
	{
		return point >= rangeStart && point <= rangeEnd;
	}
private:
	PongPaddle &pongPaddle;
	Ball &ball;
};

int main(int, char **)
{
	
#ifdef __MACOSX__
	SFMLGfx gfx;
	SFMLInput input;
#else
	HIDInput input;
	SF2DGfx gfx;

	//consoleDebugInit(debugDevice_CONSOLE);
	consoleDebugInit(debugDevice_3DMOO);
#endif
	

	PongPaddle paddle(gfx, input);
	Ball ball(gfx);
	CollisionHandler collisionHandler(paddle, ball);

	int score = 0;
	// Main loop
	while (aptMainLoop() && !input.startDown())
	{
		input.scan();
		
		paddle.update();
		ball.update();

		if (collisionHandler.checkCollision())
		{
			score++;
		}

		gfx.renderOnTop([&]{
			ball.draw();
			paddle.draw();
		});

		gfx.renderOnBottom([&]{
			char scoreBuffer[16] = { 0 };
			sprintf(scoreBuffer, "Score: %d", score);
			gfx.drawText(scoreBuffer, 10, 100);
			char foulBuffer[16] = { 0 };
			sprintf(foulBuffer, "Fouls: %d", ball.getFouls());
			gfx.drawText(foulBuffer, 10, 150);
		});


		gfx.flip();
	}
	
	return 0;
}
