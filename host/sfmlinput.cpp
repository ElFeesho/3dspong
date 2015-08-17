#include "sfmlinput.h"

#include <SFML/Window.hpp>

SFMLInput::SFMLInput()
{

}

SFMLInput::~SFMLInput()
{

}

void SFMLInput::scan()
{
	
}

bool SFMLInput::startDown()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
}

float SFMLInput::circleXAxis()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? -1.0f : (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? 1.0f : 0.0f);
}

float SFMLInput::circleYAxis()
{
	return sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? -1.0f : (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ? 1.0f : 0.0f);
}
