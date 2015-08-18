#pragma once

#include "gfx.h"
#include <SFML/Graphics.hpp>

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
	void drawText(const std::string &text, int x, int y) override;
private:
	sf::RenderWindow window;
	sf::Vector2f offset;
	sf::Font font;
};