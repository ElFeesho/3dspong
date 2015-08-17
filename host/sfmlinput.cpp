#include "input.h"

#include <SFML/Window.hpp>

Input::Input()
{

}

Input::~Input()
{

}

void Input::scan()
{
	
}

bool Input::startDown()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
}

float Input::circleXAxis()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? -1.0f : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? 1.0f : 0.0f);
}

float Input::circleYAxis()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? -1.0f : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? 1.0f : 0.0f);
}
