#pragma once
#include "object_pool.h"
#include "enemy.h"
#include "item.h"
class LevelSpawner : public Observer{
public:
	LevelSpawner(ObjectPool<Enemy> *enemy_pool, ObjectPool<Item> *item_pool);
	void init();
	void update();
	int getLevelTimer();
	void spawnEnemy(int x, int y);
	void spawnItem(int x, int y, itemType type);
	void receive(Message_Observers msg, int x, int y);
	void destroy();
private:
	ObjectPool<Enemy> *enemy_pool;
	ObjectPool<Item> *item_pool;
	int levelTimer;
};