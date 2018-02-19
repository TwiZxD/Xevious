#pragma once
#include "gameObject.h"
#include "enemyGraphicComponent.h"
#include "observer.h"

class Enemy : public GameObject {
public:
	Enemy();
	Enemy(int x, int y, EnemyGraphicComponent *graphicComponent);
	void update();
	void create(EnemyGraphicComponent *graphicComponent, int width, int height, std::vector<Observer*> *globalListeners);
	void init(int x, int y);
	void render();
	void addComponentUpdaters(Component * component);
	void addComponentListener(Component * component);
	void Receive(Message2 msg);
	void Send(Message m);
	void sendGlobal(Message_Observers m);
	void sendGlobal(Message_Observers m, int x, int y);
	std::vector<Component*> * getListeners();
	void destroy();
private:
	int life;
	void takeDamage(int damage);
	EnemyGraphicComponent *graphicComponent;
	std::vector<Component*> componentUpdateList;
	std::vector<Component*> componentListeners;
	std::vector<Observer*> *globalListeners;
};