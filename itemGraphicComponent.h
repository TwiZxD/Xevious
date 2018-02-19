#pragma once
#include "avancezlib.h"
#include "components.h"
#include "itemTypes.h"
class ItemGraphicComponent : public Component{
public :
	ItemGraphicComponent(AvancezLib * system);
	void render(int x, int y, itemType type);
	void destroy();
private:
	Sprite *rocket;
	Sprite *health;
	Sprite *laser;
};