#include "sf2dgfx.h"
#include <math.h>
#include "bold.h"

SF2DGfx::SF2DGfx() : characterMap(":-_;=+/\\abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
{
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

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

	char buffer[28] = { 0 };
	sprintf(buffer, "Max width: %d\n", maxWidth);
	svcOutputDebugString(buffer, strlen(buffer));
	

	int mapSize = (int)(ceil(sqrt(characterMap.length())));

	
	sprintf(buffer, "Texture Width: %d - %d", maxHeight * mapSize, characterMapTexture->pow2_w);
	svcOutputDebugString(buffer, strlen(buffer));

	u32 rgbaBuffer[maxWidth * maxHeight] = { 0xffffffff };
	characterMapTexture = sf2d_create_texture_mem_RGBA8((void*)rgbaBuffer, maxWidth * mapSize, maxHeight * mapSize, TEXFMT_RGBA8, SF2D_PLACE_RAM);

	unsigned int characterOffset = 0;
	
	for (unsigned int yOff = 0; yOff < mapSize*maxHeight; yOff+=maxHeight)
	{
		for (unsigned int xOff = 0; xOff < mapSize*maxWidth; xOff+=maxWidth)
		{
			xPositions[characterMap[characterOffset]] = xOff;
			yPositions[characterMap[characterOffset]] = yOff;
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
							sf2d_set_pixel(characterMapTexture, xOff+x, yOff+y, (0xffffffff));
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

SF2DGfx::~SF2DGfx()
{
	sf2d_fini();
	FT_Done_Face(font);
	FT_Done_FreeType(freetypeHandle);
}

void SF2DGfx::flip()
{
	sf2d_swapbuffers();
}

void SF2DGfx::renderOnTop(const std::function<void()> &renderBlock)
{
	sf2d_start_frame(GFX_TOP, GFX_RIGHT);
	renderBlock();
	sf2d_end_frame();
}

void SF2DGfx::renderOnBottom(const std::function<void()> &renderBlock)
{
	sf2d_start_frame(GFX_BOTTOM, GFX_RIGHT);
	renderBlock();
	sf2d_end_frame();
}

void SF2DGfx::drawRectangle(int x, int y, int w, int h, const Colour &colour)
{
	sf2d_draw_rectangle(x, y, w, h, RGBA8(colour.red, colour.green, colour.blue, colour.alpha));
}

void SF2DGfx::drawCharacter(char character, int xPos, int yPos)
{
	sf2d_draw_texture_part(characterMapTexture, xPos, yPos, xPositions[character], yPositions[character], 32, 33);
}

void SF2DGfx::drawText(const std::string &text, int xPos, int yPos) 
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