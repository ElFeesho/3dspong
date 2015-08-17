#pragma once

class Input
{
public:
	virtual ~Input() = default;

	virtual void scan() = 0;

	virtual bool startDown() = 0;

	virtual float circleXAxis() = 0;
	
	virtual float circleYAxis() = 0;
};