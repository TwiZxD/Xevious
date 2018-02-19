#include "itemBehaviourComponent.h"

itemBehaviourComponent::itemBehaviourComponent(Item * item)
{
	this->item = item;
}

void itemBehaviourComponent::update()
{
	item->setY(item->getY() + SPEED);
}
