#include "sfmlgfx.h"

#include <SFML/Graphics.hpp>


SFMLGfx::SFMLGfx() : window(sf::VideoMode(400, 480), "3dspong"), offset(0, 0)
{
	font.loadFromFile("../resources/bold.ttf");
	window.clear(sf::Color(0x40, 0x40, 0x40));
}

SFMLGfx::~SFMLGfx()
{
	
}

void SFMLGfx::flip()
{
	window.display();
	window.clear(sf::Color(0x40, 0x40, 0x40));

}

void SFMLGfx::renderOnTop(const std::function<void()> &renderBlock)
{
	offset.x = 0;
	offset.y = 0;
	renderBlock();
	sf::RectangleShape rectangle;

	rectangle.setPosition(sf::Vector2f(0, 240));
	rectangle.setSize(sf::Vector2f(40, 240));
	rectangle.setFillColor(sf::Color(0, 0, 0));
	window.draw(rectangle);
	rectangle.setPosition(sf::Vector2f(400-40, 240));
	window.draw(rectangle);
}

void SFMLGfx::renderOnBottom(const std::function<void()> &renderBlock)
{
	offset.x = 40;
	offset.y = 240;
	renderBlock();
}

void SFMLGfx::drawRectangle(int x, int y, int w, int h, const Colour &colour)
{
	sf::RectangleShape rectangle;

	rectangle.setPosition(sf::Vector2f(offset.x + x, offset.y + y));
	rectangle.setSize(sf::Vector2f(w, h));
	rectangle.setFillColor(sf::Color(colour.red, colour.green, colour.blue));
	window.draw(rectangle);
}

void SFMLGfx::drawText(const std::string &text, int x, int y) 
{
	sf::Text outputText(text, font);
	outputText.move(offset.x + x, offset.y + y);
	window.draw(outputText);
}