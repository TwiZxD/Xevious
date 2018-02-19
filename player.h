#pragma once
#include "avancezlib.h"
#include "gameObject.h"
#include "playerGraphicComponent.h"
#include "components.h"
#include "playerBehaviourComponent.h"
#include "playerOneInputComponent.h"
#include <vector>
#include "observer.h"
#include "itemTypes.h"

class Player : public GameObject {
public:
	Player(AvancezLib * system, PlayerGraphicComponent * graphicComponent, std::vector<Observer*>* globalListeners);
	void create(ObjectPool<Rocket>* rockets_pool, ObjectPool<Rocket>* missile_pool);
	void init(int x, int y);
	void update();
	void render();
	void destroy();
	void gainPowerUp(itemType type);
	void addComponentUpdaters(Component *reciever);
	void addComponentListener(Component *component);
	void addRenderComponent(Component *component);
	void gainLevel();
	int getPlayerLevel();

	PlayerGraphicComponent getGraphicsComponent();
	void takeDamage(int damage);
	int getLife();
	void Receive(Message2 msg);

	void Send(Message m);
	void sendGlobal(Message_Observers m);

	bool rocketWeaponsEnabled;
private:

	AvancezLib *system;
	Sprite *playerSprite;
	int windowWidth;
	bool playerMovingLeft;
	int life = 0;

	std::vector<Component*> componentUpdateList;
	std::vector<Component*> renderComponents;
	std::vector<Component*> componentListeners;
	std::vector<Observer*> * globalListeners;
	PlayerGraphicComponent *graphicComponent;
	PlayerOneInputController *inputComponent;
	PlayerBehaviourComponent *behaviourComponent;
	int invulnerableTimer;
	int level;

};