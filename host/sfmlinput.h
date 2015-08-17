#pragma once

#include "input.h"

class SFMLInput : public Input
{
public:
	SFMLInput();
	~SFMLInput();

	void scan() override;

	bool startDown() override;

	float circleXAxis() override;
	
	float circleYAxis() override;
};