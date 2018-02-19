#include "levelSpawner.h"
LevelSpawner::LevelSpawner(ObjectPool<Enemy>* enemy_pool, ObjectPool<Item>* item_pool) 
{
	this->enemy_pool = enemy_pool;
	this->item_pool = item_pool;
	levelTimer = 0;
}

void LevelSpawner::init() {
	levelTimer = 0;

}
void LevelSpawner::update() {
	if (levelTimer == 0) {
		spawnItem(100, 200, ROCKET);
		spawnItem(150, 200, LASER);
		spawnItem(200, 200, HEALTH);
	}
	levelTimer++;

	if (levelTimer % 330 == 0) spawnEnemy(50, -10);
	if (levelTimer % 320 == 0) spawnEnemy(100, -10);
	if (levelTimer % 420 == 0) spawnEnemy(250, -10);
	if (levelTimer % 600 == 0) spawnEnemy(350, -10);
	if (levelTimer % 300 == 0) spawnEnemy(450, -10);
}

int LevelSpawner::getLevelTimer() {
	return levelTimer;
}

void LevelSpawner::spawnEnemy(int x, int y) {
	Enemy * enemy = enemy_pool->FirstAvailable();
	if (enemy != NULL)	// rocket is NULL is the object pool can not provide an object
	{
		enemy->init(x, y);
	}
}

void LevelSpawner::spawnItem(int x, int y, itemType type) {
	Item * item = item_pool->FirstAvailable();
	if (item != NULL) {
		item->init(x, y, type);
	}
}

void LevelSpawner::receive(Message_Observers msg, int x, int y)
{
	if (msg == ENEMY_KILLED) {
		int randomValue = rand() % 1000;     // v2 in the range 0 to 1000
		
		if (randomValue < 50) {
			spawnItem(x, y, LASER);
		}
		else if (randomValue < 150) {
			spawnItem(x, y, HEALTH);
		}
	}
}

void LevelSpawner::destroy()
{
}
