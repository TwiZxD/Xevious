#pragma once
#include "components.h"
#include "rocket.h"

class PlayerRocketBehaviourComponent : public Component {
public:
	PlayerRocketBehaviourComponent(Rocket * rocket, int speed);
	void update();
private:
	Rocket *rocket;
private:
	int SPEED;
};