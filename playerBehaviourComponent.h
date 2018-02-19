#pragma once

#include "components.h"
#include "playerGraphicComponent.h"
#include "rocket.h"
#include "observer.h"
enum Direction { NORTH, WEST, EAST, SOUTH };

class Player;
class PlayerBehaviourComponent : public Component {
public:
	PlayerBehaviourComponent(Player *player, ObjectPool<Rocket> * rockets_pool, ObjectPool<Rocket> * missile_pool, std::vector<Component*> *receivers, std::vector<Observer*> *globalListeners);
	void create();
	void update();
	void destroy();
	void shoot();
	void shootMissile();
	void receive(Message msg);
	void Send(Message m);
	void sendGlobal(Message_Observers m);
	int getVelocityX();
	int getVelocityY();

private:
	int reloadTimerMissile;
	int reloadTimerLaser;
	int movementSpeed = 4;
	int x_speed = 2;
	int y_speed = 1;
	int x_velocity = 0;
	int y_velocity = 0;
	Player *player;
	std::vector<Component*> *receivers;
	std::vector<Observer*> *globalListeners;
	PlayerGraphicComponent *graphicComponent;
	ObjectPool<Rocket> * rockets_pool;
	ObjectPool<Rocket> * missile_pool;
};