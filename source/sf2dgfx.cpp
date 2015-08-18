#include "sf2dgfx.h"

#include <sf2d.h>

SF2DGfx::SF2DGfx()
{
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
}

SF2DGfx::~SF2DGfx()
{
	sf2d_fini();
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