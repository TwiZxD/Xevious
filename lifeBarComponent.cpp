#include "lifeBarComponent.h"
#include "SystemSpecifications.h"


LifeBarComponent::LifeBarComponent(AvancezLib * sýstem, Player *player)
{
	this->lifeSprite = sýstem->createSprite("res/player_front_nospeed.png");
	this->player = player;
}

void LifeBarComponent::update()
{	
	int life = player->getLife();
	for (int i = 0; i < life; i++) {
		lifeSprite->draw(21 + i * 42, windowHeight - 21);
	}
}

void LifeBarComponent::destroy() {
	if (lifeSprite != NULL) {
		lifeSprite->destroy();
		lifeSprite = NULL;
	}
}

