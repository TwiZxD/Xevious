#include "playerRocketBehaviourComponent.h"

PlayerRocketBehaviourComponent::PlayerRocketBehaviourComponent(Rocket* rocket, int speed) {
	this->rocket = rocket;
	this->SPEED = speed;
}

void PlayerRocketBehaviourComponent::update()
{
	rocket->setY(rocket->getY() - SPEED);
}
