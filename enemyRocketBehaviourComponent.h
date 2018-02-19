#pragma once
#include "components.h"
#include "rocket.h"
class EnemyRocketBehaviourComponent : public Component {
public:
	EnemyRocketBehaviourComponent(Rocket * rocket);
	void update();
	void destroy();
private:
	Rocket *rocket;
private: 
	int SPEED = 5;
};