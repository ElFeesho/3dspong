#pragma once

#include "gfx.h"
#include <SFML/Graphics.hpp>

#include <map>

#include <ft2build.h>                                            
#include FT_FREETYPE_H                                           
#include FT_OUTLINE_H  

struct Size
{
	Size(int width, int height) : w(width), h(height){}
	~Size() {}
	int w;
	int h;
};

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

	void drawCharacter(char character, int x, int y) override;

private:
	sf::RenderWindow window;
	sf::Vector2f offset;
	
	FT_Library freetypeHandle;
	FT_Face font;
	std::string characterMap;
	std::map<char, unsigned int> characterWidths;
	std::map<char, unsigned int> characterHeights;
	std::map<char, unsigned int> spacing;
	std::map<char, unsigned int> baseline;
	std::map<char, sf::Vector2i> positions;
	sf::RenderTexture characterMapTexture;

};