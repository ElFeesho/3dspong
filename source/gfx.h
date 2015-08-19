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
	virtual ~Gfx() = default;

	virtual void flip() = 0;

	virtual void renderOnTop(const std::function<void()> &renderBlock) = 0;
	virtual void renderOnBottom(const std::function<void()> &renderBlock) = 0;

	// Drawing methods
	virtual void drawRectangle(int x, int y, int w, int h, const Colour &colour) = 0;
	virtual void drawText(const std::string &text, int x, int y) = 0;
	virtual void drawCharacter(char character, int x, int y) = 0;
};