#pragma once

#include <3ds.h>

class Input
{
public:
	Input();

	~Input();

	void scan();

	bool startDown();

private:
	int keys;
	circlePosition circle;
};