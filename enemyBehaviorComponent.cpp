#include "enemyBehaviorComponent.h"

#include "SystemSpecifications.h"
EnemyBehaviorComponent::EnemyBehaviorComponent(Enemy * enemy, ObjectPool<Rocket>* rockets_pool, std::vector<Component*>* receivers, std::vector<Observer*>* globalListeners)
{
	this->enemy = enemy;
	this->rockets_pool = rockets_pool;
	timer = 0;
	this->receivers = receivers;
	this->globalListeners = globalListeners;
}

void EnemyBehaviorComponent::update()
{
	timer++;
	if (timer >= 1000) {
		timer = 0;
	}
	if ((timer % 120) == 0) {
		shoot();
	}
	 enemy->setY(enemy->getY() + 1);
	 if (enemy->getY() > windowHeight + 100) {
		 enemy->enabled = false;
	 }

}

void EnemyBehaviorComponent::destroy()
{
}

void EnemyBehaviorComponent::shoot()
{
	Rocket * rocket = rockets_pool->FirstAvailable();
	if (rocket != NULL)	// rocket is NULL is the object pool can not provide an object
	{	
		sendGlobal(PLAY_ENEMY_FIRE);
		rocket->init(enemy->getX(), enemy->getY());
	}
}

void EnemyBehaviorComponent::Send(Message m)
{
	for (auto i = 0; i < receivers->size(); i++)
	{
		receivers->at(i)->receive(m);
	}
}

void EnemyBehaviorComponent::sendGlobal(Message_Observers m)
{
	for (auto i = 0; i < globalListeners->size(); i++)
	{
		globalListeners->at(i)->receive(m);
	}
}
