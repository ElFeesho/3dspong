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