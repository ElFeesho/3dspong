#pragma once

class Gfx;

class Ball
{
public:
	Ball(Gfx &graphics);

	~Ball();

	void setX(float xVal);

	void setY(float yVal);

	int getX();

	int getY();

	void update();

	void flipYSpeed();

	void flipXSpeed();

	void draw();

	int getFouls();

private:
	float xspeed { 2.5f };
	float yspeed { 2.5f };
	int y { 80 };
	int x { 80 };
	int fouls { 0 };
	Gfx &gfx;
};