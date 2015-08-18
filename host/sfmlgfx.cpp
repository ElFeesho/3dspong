#include "sfmlgfx.h"

#include <SFML/Graphics.hpp>

static sf::RenderWindow *window;

SFMLGfx::SFMLGfx()
{
	window = new sf::RenderWindow(sf::VideoMode(400, 240), "3dspong");
	window->clear(sf::Color(0x40, 0x40, 0x40));

}

SFMLGfx::~SFMLGfx()
{
	
}

void SFMLGfx::flip()
{
	window->display();
	window->clear(sf::Color(0x40, 0x40, 0x40));
}

void SFMLGfx::renderOnTop(const std::function<void()> &renderBlock)
{
	renderBlock();
	
}

void SFMLGfx::renderOnBottom(const std::function<void()> &renderBlock)
{
	renderBlock();
	
}

void SFMLGfx::drawRectangle(int x, int y, int w, int h, const Colour &colour)
{
	sf::RectangleShape rectangle;

	rectangle.setPosition(sf::Vector2f(x, y));
	rectangle.setSize(sf::Vector2f(w, h));
	rectangle.setFillColor(sf::Color(colour.red, colour.green, colour.blue));
	window->draw(rectangle);
}