#pragma once
#pragma once
#include "components.h"
#include "item.h"
class itemBehaviourComponent : public Component {
public:
	itemBehaviourComponent(Item * item);
	void update();
private:
	Item *item;
private:
	int SPEED = 1;
};