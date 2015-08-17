#pragma once

#include "input.h"

class HIDInput : public Input
{
public:
	HIDInput();
	~HIDInput() = default;

	void scan() override;

	bool startDown() override;

	float circleXAxis() override;
	
	float circleYAxis() override;
private:
	int keys { 0 };
};