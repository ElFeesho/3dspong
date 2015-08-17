#include <3ds.h>
#include <sf2d.h>
#include <stdio.h>
#include <functional>

class Gfx
{
public:
	Gfx()
	{
		sf2d_init();
		sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	}

	~Gfx()
	{
		sf2d_fini();
	}

	void flip()
	{
		sf2d_swapbuffers();
	}

	void renderOnTop(const std::function<void()> &renderBlock)
	{
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		renderBlock();
		sf2d_end_frame();
	}

	void renderOnBottom(const std::function<void()> &renderBlock)
	{
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
		renderBlock();
		sf2d_end_frame();
	}
};

class Input
{
public:
	Input()
	{

	}

	~Input()
	{

	}

	void scan()
	{
		hidScanInput();
		hidCircleRead(&circle);
		keys = hidKeysHeld();
	}

	bool startDown()
	{
		return keys & KEY_START;
	}

private:
	int keys;
	circlePosition circle;
};

int main(int argc, char **argv)
{
	Gfx gfx;
	Input input;

	// Main loop
	while (aptMainLoop() && !input.startDown())
	{
		input.scan();
		gfx.renderOnTop([&](){
			sf2d_draw_rectangle(20, 60, 40, 40, RGBA8(0xFF, 0x00, 0x00, 0xFF));
		});
		gfx.renderOnBottom([&](){
			sf2d_draw_rectangle(20, 60, 40, 40, RGBA8(0xFF, 0x00, 0x00, 0xFF));
		});
		gfx.flip();
	}
	
	return 0;
}
