#include "miniRT.h"

void	windowSetVars(void* self, double x, double y) {
	Window*	this;

	this = self;
	this->x = x;
	this->y = y;
	// this->viewport.changeCoords(&this->viewport, x * VH / WIDTH - 1, (y * VW / HEIGHT - 1) * - 1, -1);
}