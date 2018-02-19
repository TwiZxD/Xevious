#pragma once
#include "components.h"
#include  "player.h"

class LifeBarComponent : public Component {
public:
	LifeBarComponent(AvancezLib * s�stem, Player *player);
	void update();
	void destroy();
private:
	Sprite *lifeSprite;
	Player *player;
};