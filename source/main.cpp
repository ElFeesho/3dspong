#include <3ds.h>
#include <sf2d.h>
#include <stdio.h>
#include <functional>

#include "gfx.h"
#include "input.h"

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
