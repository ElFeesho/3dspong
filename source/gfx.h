#pragma once

#include <functional>

struct Colour
{
	Colour(int r, int g, int b, int a = 255) : red(r), green(g), blue(b), alpha(a) {}

	~Colour() {}

	const int red, green, blue, alpha;
};

class Gfx
{
public:
	Gfx();

	~Gfx();

	void flip();

	void renderOnTop(const std::function<void()> &renderBlock);

	void renderOnBottom(const std::function<void()> &renderBlock);

	// Drawing methods

	void drawRectangle(int x, int y, int w, int h, const Colour &colour);
};