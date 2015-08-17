#include "HIDInput.h"

#include <3ds.h>

HIDInput::HIDInput()
{

}

void HIDInput::scan() {
	hidScanInput();
	keys = hidKeysHeld();
}

bool HIDInput::startDown() {
	return keys & KEY_START;
}

float HIDInput::circleXAxis() {
	return keys & KEY_DLEFT ? -1.0f : (keys & KEY_DRIGHT ? 1.0f : 0.0f);
}
	
float HIDInput::circleYAxis() {
	return keys & KEY_DUP ? -1.0f : (keys & KEY_DDOWN ? 1.0f : 0.0f);
}