#pragma once

#include "gfx.h"

class SFMLGfx : public Gfx
{
public:
	SFMLGfx();
	~SFMLGfx();

	void flip() override;

	void renderOnTop(const std::function<void()> &renderBlock) override;
	void renderOnBottom(const std::function<void()> &renderBlock) override;

	// Drawing methods
	void drawRectangle(int x, int y, int w, int h, const Colour &colour) override;
};