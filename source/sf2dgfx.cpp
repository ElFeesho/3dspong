#include "sf2dgfx.h"

#include <exception>

#include <sf2d.h>

#include "bold.h"

SF2DGfx::SF2DGfx()
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

void SF2DGfx::drawText(const std::string &text, int xPos, int yPos) 
{
	for(unsigned int i = 0; i < text.length(); i++)
	{
		if (text[i] == ' ')
		{
			xPos += 20;
			continue;
		}
		int glyphIndex = FT_Get_Char_Index(font, text[i]);
		if (FT_Load_Glyph(font, glyphIndex, 0) == 0 && FT_Render_Glyph( font->glyph, FT_RENDER_MODE_NORMAL) == 0)
		{
			int rowStart = 0;
			for(unsigned int y = 0; y < font->glyph->bitmap.rows; y++)
			{
				for(unsigned int x = 0; x < font->glyph->bitmap.width; x++)
				{
					unsigned char alpha = font->glyph->bitmap.buffer[rowStart + x];
					if(alpha != 0)
					{
						sf2d_draw_rectangle(xPos + x + font->glyph->bitmap_left, yPos + y-font->glyph->bitmap.rows, 1, 1, (0xffffff << 8) + alpha);
					}
				}
				rowStart += font->glyph->bitmap.pitch;
			}
		}
		xPos += font->glyph->bitmap.width + 2;
	}
}