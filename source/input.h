#pragma once

#include <3ds.h>

class Input
{
public:
	Input();

	~Input();

	void scan();

	bool startDown();

	float circleXAxis();
	
	float circleYAxis();

private:
	int keys;
	circlePosition circle;
};