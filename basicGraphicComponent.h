#pragma once
#include "components.h"
#include "avancezlib.h"
class BasicGraphicComponent : public Component {
public:
	BasicGraphicComponent(Sprite *sprite);
	void render(int x, int y);
	void destroy();
private:
	Sprite *sprite;
};