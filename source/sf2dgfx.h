#pragma once

#include <sf2d.h>

#include "gfx.h"

#include <string>
#include <map>

#include <ft2build.h>                                            
                                                                   
#include FT_FREETYPE_H                                           
#include FT_OUTLINE_H  


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
	void drawText(const std::string &text, int x, int y) override;

	void drawCharacter(char character, int x, int y);
private:
	FT_Library freetypeHandle;
	FT_Face font;
	std::string characterMap;
	std::map<char, unsigned int> characterWidths;
	std::map<char, unsigned int> characterHeights;
	std::map<char, unsigned int> spacing;
	std::map<char, unsigned int> baseline;
	std::map<char, unsigned int> xPositions;
	std::map<char, unsigned int> yPositions;
	sf2d_texture *characterMapTexture;
};