#include "sfmlgfx.h"

#include <SFML/Graphics.hpp>

#include "../source/bold.h"
#include <math.h>

SFMLGfx::SFMLGfx() : window(sf::VideoMode(400, 480), "3dspong"), offset(0, 0), characterMap(":-_;=+/\\abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
{
	window.clear(sf::Color(0x40, 0x40, 0x40));

	FT_Init_FreeType(&freetypeHandle);
	
	if (FT_New_Memory_Face(freetypeHandle, (const FT_Byte*)bold_ttf, bold_ttf_len, 0, &font) != 0)
	{
		exit(-1);
	}
	FT_Set_Char_Size(
          font, 
          0,    
          8*64,
          300,  
          300 );
	
	unsigned int maxWidth = 0;
	unsigned int maxHeight = 0;
	for(const char &c : characterMap)
	{
		int glyphIndex = FT_Get_Char_Index(font, c);
		if (FT_Load_Glyph(font, glyphIndex, FT_LOAD_DEFAULT|FT_LOAD_NO_BITMAP) == 0)
		{
			characterWidths[c] = (font->glyph->metrics.width/64);
			maxWidth = characterWidths[c] > maxWidth ? characterWidths[c] : maxWidth;
			characterHeights[c] = (font->glyph->metrics.height/64);
			maxHeight = characterHeights[c] > maxHeight ? characterHeights[c] : maxHeight;
			spacing[c] = font->glyph->metrics.horiBearingX/64;
			baseline[c] = font->glyph->metrics.horiBearingY/64;
		}
	}
	printf("Max width: %d\n", maxWidth);
	printf("Max Height: %d\n", maxHeight);
	int mapSize = (int)(ceil(sqrt(characterMap.length())));

	characterMapTexture.create(maxWidth * mapSize, maxHeight * mapSize);
	characterMapTexture.display();
	characterMapTexture.clear(sf::Color(0, 0, 0, 0));
	unsigned int characterOffset = 0;
	sf::RectangleShape rectangle;

	for (unsigned int yOff = 0; yOff < mapSize*maxHeight; yOff+=maxHeight)
	{
		for (unsigned int xOff = 0; xOff < mapSize*maxWidth; xOff+=maxWidth)
		{
			positions[characterMap[characterOffset]] = sf::Vector2i(xOff, yOff);
			int glyphIndex = FT_Get_Char_Index(font, characterMap[characterOffset++]);
			if (FT_Load_Glyph(font, glyphIndex, 0) == 0 && FT_Render_Glyph(font->glyph, FT_RENDER_MODE_NORMAL) == 0)
			{
				int rowStart = 0;
				for(unsigned int y = 0; y < font->glyph->bitmap.rows; y++)
				{
					for(unsigned int x = 0; x < font->glyph->bitmap.width; x++)
					{
						unsigned char alpha = font->glyph->bitmap.buffer[rowStart + x];
						if(alpha != 0)
						{
							rectangle.setPosition(sf::Vector2f(xOff+x, yOff+y));
							rectangle.setSize(sf::Vector2f(1, 1));
							rectangle.setFillColor(sf::Color(255, 255, 255, 255));
							characterMapTexture.draw(rectangle);
						}
					}
					rowStart += font->glyph->bitmap.pitch;
				}
			}

			if(characterOffset > characterMap.length())
			{
				break;
			}
		}
	}
}

SFMLGfx::~SFMLGfx()
{
	FT_Done_Face(font);
	FT_Done_FreeType(freetypeHandle);
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

void SFMLGfx::drawCharacter(char character, int xPos, int yPos)
{
	sf::Sprite glyph(characterMapTexture.getTexture(), sf::IntRect(positions[character].x, positions[character].y, 32, 33));
	glyph.setPosition(sf::Vector2f(offset.x + xPos, offset.y + yPos));
	window.draw(glyph);
}

void SFMLGfx::drawText(const std::string &text, int xPos, int yPos) 
{
	for (const char &c : text)
	{
		if(c == ' ')
		{
			xPos += characterWidths['M'];
		}
		else
		{
			drawCharacter(c, xPos, yPos-baseline[c]);
			xPos += characterWidths[c]+1;
		}
	}
}