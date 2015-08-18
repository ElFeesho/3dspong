#pragma once

#include "gfx.h"

class SF2DGfx : public Gfx
{
public:
	SF2DGfx();
	~SF2DGfx();

	void flip() override;

	void renderOnTop(const std::function<void()> &renderBlock) override;
	void renderOnBottom(const std::function<void()> &renderBlock) override;

	// Drawing methods
	void drawRectangle(int x, int y, int w, int h, const Colour &colour) override;
};