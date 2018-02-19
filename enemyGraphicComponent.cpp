#include "enemyGraphicComponent.h"

EnemyGraphicComponent::EnemyGraphicComponent(AvancezLib *system) {
	this->sprite = system->createSprite("res/fighter_1.png");
}

void EnemyGraphicComponent::render(int x, int y) {
	sprite->draw(x, y);
}

void EnemyGraphicComponent::destroy()
{
	if (sprite != NULL) {
		sprite->destroy();
		sprite = NULL;
	}
}

void EnemyGraphicComponent::receive(Message msg)
{
}
