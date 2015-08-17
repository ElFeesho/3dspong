#include "input.h"

Input::Input()
{

}

Input::~Input()
{

}

void Input::scan()
{
	hidScanInput();
	hidCircleRead(&circle);
	keys = hidKeysHeld();
}

bool Input::startDown()
{
	return keys & KEY_START;
}
