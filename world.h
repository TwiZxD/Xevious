#pragma once

#include "player.h"
#include "enemy.h"
#include "enemyGraphicComponent.h"
#include "avancezlib.h"
#include "rocket.h"
#include "gameObject.h"
#include <vector>
#include "playerGraphicComponent.h"
#include "basicGraphicComponent.h"
#include "playerBehaviourComponent.h"
#include "enemyRocketBehaviourComponent.h"
#include "playerRocketBehaviourComponent.h"
#include "enemyBehaviorComponent.h"
#include "levelSpawner.h"
#include "lifeBarComponent.h"
#include "gameState.h"
#include "SDL.h"
#include "SystemSpecifications.h"
#include "observer.h"
#include "scoreHandler.h"
#include "item.h"
#include "itemGraphicComponent.h"
#include "itemBehaviourComponent.h"

class World : public GameState{
private:
	std::vector<Observer*> *globalListeners;
	statusAction gameStatus = CONTINUE;
	ObjectPool<Player> player_pool; //For future multiplayer
	ObjectPool<Enemy> enemy_pool;
	ObjectPool<Rocket> player_rocket_pool;
	ObjectPool<Rocket> player_missile_pool;
	ObjectPool<Rocket> enemy_rocket_pool;
	ObjectPool<Item> item_pool;

	Player *player;
	bool pause = false;
	AvancezLib *system;
	PlayerGraphicComponent *playerGraphicComponent;
	PlayerBehaviourComponent *playerBehaviourComponent;
	EnemyGraphicComponent *enemyGraphicComponent;
	int numEntities_;

	void playerInputs();
	std::vector<GameObject*> game_objects;
	LevelSpawner *levelSpawner;
	ScoreHandler * scoreHandler;

public:
	World(AvancezLib *system, std::vector<Observer*> *globalListeners);
	void init();
	void addObject(GameObject * object);
	void spawnEnemy(int x, int y);
	void collistionDetection();
	bool checkCollision(int object_x, int object_y, int objectWidth, int objectHeight, int other_x, int other_y, int otherWidth, int otherHeight);
	void checkWinningCondition();
	void update();
	void render();
	statusAction getStatus();
	void destroy();
};