#include "enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(int x, int y, EnemyGraphicComponent *graphicComponent )
{
	this->graphicComponent = graphicComponent;
}
void Enemy::update()
{
	for (int i = 0; i < componentUpdateList.size(); i++) {
		componentUpdateList[i]->update();
	}
}

void Enemy::create(EnemyGraphicComponent * graphicComponent, int width, int height, std::vector<Observer*>* globalListeners)
{
	this->graphicComponent = graphicComponent;
	setWidth(width);
	setHeight(height);
	this->globalListeners = globalListeners;
}


void Enemy::init(int x, int y)
{
	life = 13;
	setX(x);
	setY(y);
	enabled = true;
}

void Enemy::render()
{
	graphicComponent->render(getX(), getY());
}

void Enemy::addComponentUpdaters(Component * component)
{
	componentUpdateList.push_back(component);
}

void Enemy::addComponentListener(Component *component)
{
	componentListeners.push_back(component);
}

void Enemy::Receive(Message2 msg)
{
	if (msg == HIT) {
		takeDamage(1);
	} else if (msg == HIT_MISSILE) {
		takeDamage(20);
	}
}

void Enemy::Send(Message m)
{
	for (auto i = 0; i < componentListeners.size(); i++)
	{
		componentListeners[i]->receive(m);
	}
}

void Enemy::sendGlobal(Message_Observers m)
{
	for (auto i = 0; i < globalListeners->size(); i++)
	{
		globalListeners->at(i)->receive(m);
	}
}

void Enemy::sendGlobal(Message_Observers m, int x, int y)
{
	for (auto i = 0; i < globalListeners->size(); i++)
	{
		globalListeners->at(i)->receive(m, x, y);
	}
}

std::vector<Component*> * Enemy::getListeners()
{
	return &componentListeners;
}

void Enemy::destroy()
{ 
	for (int i = 0; i < componentUpdateList.size(); i++) {
		if (componentUpdateList[i] != NULL) {
		//	componentUpdateList[i];
			delete componentUpdateList[i];
			componentUpdateList[i] = NULL;
		}
	}
	for (int i = 0; i < componentListeners.size(); i++) {
		if (componentListeners[i] != NULL) {
			delete componentListeners[i];
			componentListeners[i] = NULL;
		}
	}

}

void Enemy::takeDamage(int damage)
{
	life = life - damage;
	sendGlobal(PLAY_ENEMY_HIT);
	if (life <= 0 && enabled) {
		sendGlobal(ENEMY_KILLED);
		int x = getX();
		int y = getY();
		sendGlobal(ENEMY_KILLED, x, y);
		enabled = false;
	}
}
