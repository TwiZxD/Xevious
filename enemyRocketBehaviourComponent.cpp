#include "enemyRocketBehaviourComponent.h"


EnemyRocketBehaviourComponent::EnemyRocketBehaviourComponent(Rocket* rocket) {
	this->rocket = rocket;
}

void EnemyRocketBehaviourComponent::update()
{
	rocket->setY(rocket->getY() + SPEED);
}

void EnemyRocketBehaviourComponent::destroy()
{
}
