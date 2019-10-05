#pragma once

struct Vec2 {
	int x = 0;
	int y = 0;
};


bool isCollaiding(SDL_Rect rectA, SDL_Rect mouse) {

	if (((mouse.x + mouse.w) > rectA.x && (rectA.x + rectA.w) > mouse.x) && ((mouse.y + mouse.h) > rectA.y &&  mouse.y < (rectA.y + rectA.h))) {
		return true;
	}
	else
		return false;

};