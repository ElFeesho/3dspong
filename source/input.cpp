#include "input.h"
#include <3ds.h>

Input::Input()
{

}

Input::~Input()
{

}

void Input::scan()
{
	hidScanInput();
	//hidCircleRead(&circle);
	keys = hidKeysHeld();
}

bool Input::startDown()
{
	return keys & KEY_START;
}

float Input::circleXAxis()
{
	return keys & KEY_DLEFT ? -1.0f : (keys & KEY_DRIGHT ? 1.0f : 0.0f);
}

float Input::circleYAxis()
{
	return keys & KEY_DUP ? -1.0f : (keys & KEY_DDOWN ? 1.0f : 0.0f);
}
