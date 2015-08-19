#pragma once

#include "gfx.h"

#include <string>
#include <vector>

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

	Size measureText(const std::string &text);
private:
	FT_Library freetypeHandle;
	FT_Face font;
	std::string characterMap;
	std::vector<int> characterWidths;
	std::vector<int> characterHeights;
};