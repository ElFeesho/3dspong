#include "sf2dgfx.h"

#include <exception>

#include <sf2d.h>

#include "bold.h"

SF2DGfx::SF2DGfx() : characterMap("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
{
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
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));

	for(unsigned int i = 0; i < characterMap.length(); i++)
	{
		int glyphIndex = FT_Get_Char_Index(font, characterMap[i]);
		if (FT_Load_Glyph(font, glyphIndex, 0) == 0 && FT_Render_Glyph(font->glyph, FT_RENDER_MODE_NORMAL) == 0)
		{
			characterWidths.push_back(font->glyph->bitmap.width);
			characterHeights.push_back(font->glyph->bitmap.rows);
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
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
	renderBlock();
	sf2d_end_frame();
}

void SF2DGfx::renderOnBottom(const std::function<void()> &renderBlock)
{
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
	renderBlock();
	sf2d_end_frame();
}

void SF2DGfx::drawRectangle(int x, int y, int w, int h, const Colour &colour)
{
	sf2d_draw_rectangle(x, y, w, h, RGBA8(colour.red, colour.green, colour.blue, colour.alpha));
}

Size SF2DGfx::measureText(const std::string &text)
{
	unsigned int w = 0;
	unsigned int h = 0;
	for(unsigned int i = 0; i < text.length(); i++)
	{
		if (text[i] == ' ')
		{
			w += 20;
			continue;
		}

		int glyphIndex = FT_Get_Char_Index(font, text[i]);
		if (FT_Load_Glyph(font, glyphIndex, 0) == 0 && FT_Render_Glyph(font->glyph, FT_RENDER_MODE_NORMAL) == 0)
		{
			w += font->glyph->bitmap.width;
			h = font->glyph->bitmap.rows > h ? font->glyph->bitmap.rows : h;
		}
	}

	return Size(w, h);
}

void SF2DGfx::drawCharacter(char character, int xPos, int yPos)
{
	unsigned int pos = characterMap.find(character);
	if (pos != std::string::npos)
	{
		int width = characterWidths[pos];
		int height = characterHeights[pos];
		unsigned char glyphBuffer[width*4*height] = { 0 };
		
		int glyphIndex = FT_Get_Char_Index(font, character);
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
						glyphBuffer[y * width * 3 + x] = alpha;
						glyphBuffer[y * width * 3 + x + 1] = alpha;
						glyphBuffer[y * width * 3 + x + 2] = alpha;
						glyphBuffer[y * width * 3 + x + 3] = alpha;
					}
				}
				rowStart += font->glyph->bitmap.pitch;
			}
		}
		sf2d_texture *offscreen = sf2d_create_texture_mem_RGBA8(glyphBuffer, width, height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
		sf2d_draw_texture(offscreen, xPos, yPos);
		sf2d_free_texture(offscreen);
	}
}

void SF2DGfx::drawText(const std::string &text, int xPos, int yPos) 
{
	// Size textSize = measureText(text);
	// unsigned char textureBuffer[textSize.w * textSize.h] = { 0xff };
					
	// for(unsigned int i = 0; i < text.length(); i++)
	// {
	// 	if (text[i] == ' ')
	// 	{
	// 		xPos += 20;
	// 		continue;
	// 	}
	// 	int glyphIndex = FT_Get_Char_Index(font, text[i]);
	// 	if (FT_Load_Glyph(font, glyphIndex, 0) == 0 && FT_Render_Glyph( font->glyph, FT_RENDER_MODE_NORMAL) == 0)
	// 	{
	// 		int rowStart = 0;
	// 		for(unsigned int y = 0; y < font->glyph->bitmap.rows; y++)
	// 		{
	// 			for(unsigned int x = 0; x < font->glyph->bitmap.width; x++)
	// 			{
	// 				unsigned char alpha = font->glyph->bitmap.buffer[rowStart + x];
	// 				if(alpha != 0)
	// 				{
	// 					textureBuffer[xPos + x + y*textSize.w] = alpha;
	// 				}
	// 			}
	// 			rowStart += font->glyph->bitmap.pitch;
	// 		}
	// 	}
	// }
	// sf2d_texture *offscreen = sf2d_create_texture_mem_RGBA8((const void*)textureBuffer, textSize.w, textSize.h, TEXFMT_A8, SF2D_PLACE_RAM);
	
	// sf2d_draw_texture_blend(offscreen, xPos, yPos, 0xff00ffff);

	// sf2d_free_texture(offscreen);
	drawCharacter('M', xPos, yPos);
}