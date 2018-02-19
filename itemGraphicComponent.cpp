#include "itemGraphicComponent.h"

ItemGraphicComponent::ItemGraphicComponent(AvancezLib * system)
{
	this->rocket = system->createSprite("res/rocket_item.png");
	this->health = system->createSprite("res/health_item.png");
	this->laser = system->createSprite("res/laser_item.png");
}

void ItemGraphicComponent::render(int x, int y, itemType type)
{
	switch (type)
	{
	case LASER:
		laser->draw(x, y);
		break;
	case HEALTH:
		health->draw(x, y);
		break;
	case ROCKET:
		rocket->draw(x, y);
		break;
	default:
		break;
	}
}

void ItemGraphicComponent::destroy()
{
//	rocket->destroy();

	if (rocket != NULL) {
		rocket->destroy();
		rocket = NULL;
	}
	if (health != NULL) {
		health->destroy();
		health = NULL;
	}
	//health->destroy();
	//laser->destroy();
	if (laser != NULL) {
		laser->destroy();
		laser = NULL;
	}
}
