#include "basicGraphicComponent.h"

BasicGraphicComponent::BasicGraphicComponent(Sprite *sprite) {
	this->sprite = sprite;
}

void BasicGraphicComponent::render(int x, int y) {
	sprite->draw(x, y);
}

void BasicGraphicComponent::destroy()
{	
	if (sprite != NULL) {
		sprite->destroy();
		sprite = NULL;
	}
}
