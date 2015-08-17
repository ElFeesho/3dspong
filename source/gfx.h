#pragma once

#include <functional>


class Gfx
{
public:
	Gfx();

	~Gfx();

	void flip();

	void renderOnTop(const std::function<void()> &renderBlock);

	void renderOnBottom(const std::function<void()> &renderBlock);
};