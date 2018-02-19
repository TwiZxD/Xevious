#pragma once
#include "components.h"
#include "rocket.h"
#include "enemy.h"
#include "observer.h"
class Enemy;
class EnemyBehaviorComponent : public Component {

public:
	EnemyBehaviorComponent(Enemy * enemy, ObjectPool<Rocket> * rockets_pool, std::vector<Component*> *receivers, std::vector<Observer*>* globalListeners);
	void update();
	void destroy();

private:
	int timer;
	
	Enemy *enemy;
	ObjectPool<Rocket> * rockets_pool;
	void sendGlobal(Message_Observers m);
	std::vector<Component*> *receivers;
	std::vector<Observer*> *globalListeners;
	
	void shoot();
	void Send(Message m);
};