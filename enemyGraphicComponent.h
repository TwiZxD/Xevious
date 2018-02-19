#pragma once
#include "components.h"
#include "avancezlib.h"

class EnemyGraphicComponent : public Component {
public:
	EnemyGraphicComponent(AvancezLib *system);
	void render(int x, int y);
	void destroy();
	void receive(Message msg);
private:
	Sprite *sprite;
};