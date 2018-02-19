#pragma once
#include "playerBehaviourComponent.h"
#include "player.h"
#include "SystemSpecifications.h"


PlayerBehaviourComponent::PlayerBehaviourComponent(Player * player, ObjectPool<Rocket>* rockets_pool, ObjectPool<Rocket>* missile_pool, std::vector<Component*>* receivers, std::vector<Observer*>* globalListeners)
{
	this->player = player;
	this->rockets_pool = rockets_pool;
	this->missile_pool = missile_pool;
	this->receivers = receivers;
	this->globalListeners = globalListeners;
	reloadTimerLaser = 0;
	reloadTimerMissile = 0;
}

void PlayerBehaviourComponent::update()
{
	if (reloadTimerLaser > 0) {
		reloadTimerLaser--;
	}
	if (reloadTimerMissile > 0) {
		reloadTimerMissile--;
	}
	if (y_velocity != 0 || x_velocity != 0)
	{
		player->setX(player->getX() + x_velocity * movementSpeed * x_speed);
		if (player->getX()  < 0) {
			player->setX(0);
		}
		else if (player->getX() > (windowWidth)) {
			player->setX(windowWidth);
		}
		player->setY(player->getY() + y_velocity * movementSpeed * y_speed);
		if (player->getY()  < 0) {
			player->setY(0);
		}
		else if (player->getY() > (windowHeight )) {
			player->setY(windowHeight);
		}
	}
	y_velocity = 0;
	x_velocity = 0;
	
}

void PlayerBehaviourComponent::destroy()
{
}

void PlayerBehaviourComponent::shoot() {

	int level = player->getPlayerLevel();

	bool soundPlayed = false;
	if (level == 0) {
		Rocket * rocket = rockets_pool->FirstAvailable();
		if (rocket != NULL)
		{
			sendGlobal(PLAYLASER);
			rocket->init(player->getX(), player->getY());

		}
	}
	else {
		for (int i = 0; i < level; i++) {
			Rocket * rocket = rockets_pool->FirstAvailable();
			if (rocket != NULL)	
			{	
				if(!soundPlayed){
					sendGlobal(PLAYLASER);
					soundPlayed = true;
				}
				
				rocket->init(player->getX() - 5 - (4 * i), player->getY());

			}
			Rocket* rocket2 = rockets_pool->FirstAvailable();
			if (rocket2 != NULL)
			{
				rocket2->init(player->getX() + 5 + (4 * i), player->getY());

			}
		}
	}	
}

void PlayerBehaviourComponent::shootMissile()
{
	Rocket * rocket = missile_pool->FirstAvailable();
	if (rocket != NULL)	
	{
		sendGlobal(PLAY_MISSILE_FIRE);
		rocket->init(player->getX(), player->getY());

	}
}

void PlayerBehaviourComponent::receive(Message msg) {
	if (msg == INPUT_SPACE) {
		int level = player->getPlayerLevel();

		if (reloadTimerLaser < 1) {
			shoot();
			reloadTimerLaser = 4 + 1 * level;
		}
		if (reloadTimerMissile < 1 && player->rocketWeaponsEnabled) {	
			shootMissile();
			reloadTimerMissile = 80;
		}

	}
	if (msg == INPUT_UP) {
		y_velocity = -1;
	}
	else if (msg == INPUT_DOWN) {
		y_velocity = 1;
	}
	if (msg == INPUT_LEFT) {
		x_velocity = -1;
	}
	else if (msg == INPUT_RIGHT) {
		x_velocity = 1;
	}
}

void PlayerBehaviourComponent::Send(Message m)
{
	for (auto i = 0; i < receivers->size(); i++)
	{
		receivers->at(i)->receive(m);
	}
}

void PlayerBehaviourComponent::sendGlobal(Message_Observers m)
{
	for (auto i = 0; i < globalListeners->size(); i++)
	{
		globalListeners->at(i)->receive(m);
	}
}

int PlayerBehaviourComponent::getVelocityX()
{
	return x_velocity;
}

int PlayerBehaviourComponent::getVelocityY()
{
	return y_velocity;
}
