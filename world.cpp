#include "world.h"
Sprite * item_rocket_sprite;
PlayerRocketBehaviourComponent *rocketBehavior;
BasicGraphicComponent *missileGraphic;
BasicGraphicComponent *rocketGraphic;
ItemGraphicComponent *itemGrapicComponent;
LifeBarComponent *lifeBar;
Sprite *rocketSprite;
Sprite *missileSprite;
BasicGraphicComponent *enemyRocketGraphic;
Sprite *enemyRocketSprite;
EnemyGraphicComponent *enemyGraphic;

World::World(AvancezLib * system, std::vector<Observer*>* globalListeners) {
	this->system = system;
	this->globalListeners = globalListeners;
	
	scoreHandler = new ScoreHandler(system);
	globalListeners->push_back(scoreHandler);

	//Create Player
	playerGraphicComponent = new PlayerGraphicComponent(system);
	player = new Player(system, playerGraphicComponent, globalListeners);
	addObject(player);
	lifeBar = new LifeBarComponent(system, player);
	player->addRenderComponent(lifeBar);
	player->create(&player_rocket_pool, &player_missile_pool);
	player->init(windowWidth / 2, windowHeight - 32);
	

	//Create Rockets pool for player
	player_rocket_pool.Create(200);
	rocketSprite = system->createSprite("res/lasershot.png");
	rocketGraphic = new BasicGraphicComponent(rocketSprite);
	
	for (auto rocket = player_rocket_pool.pool.begin(); rocket != player_rocket_pool.pool.end(); rocket++) {
		rocketBehavior = new PlayerRocketBehaviourComponent((*rocket),5);
		(*rocket)->create(rocketGraphic, rocketBehavior, 3, 9);
		addObject(*rocket);
	}

	//Create Missile pool for player
	player_missile_pool.Create(20);
	missileSprite = system->createSprite("res/rocket_full.png");
	missileGraphic = new BasicGraphicComponent(missileSprite);
	for (auto missile = player_missile_pool.pool.begin(); missile != player_missile_pool.pool.end(); missile++) {
		PlayerRocketBehaviourComponent *missileBehavior = new PlayerRocketBehaviourComponent((*missile),3);
		(*missile)->create(missileGraphic, missileBehavior, 3, 9);
		addObject(*missile);
	}

	//Create Rockets pool for Enemies
	enemy_rocket_pool.Create(20);
	enemyRocketSprite = system->createSprite("res/glowingLaser.png");
	enemyRocketGraphic = new BasicGraphicComponent(enemyRocketSprite);
	for (auto rocket = enemy_rocket_pool.pool.begin(); rocket != enemy_rocket_pool.pool.end(); rocket++) {
		EnemyRocketBehaviourComponent *rocketBehavior = new EnemyRocketBehaviourComponent((*rocket));
		(*rocket)->create(enemyRocketGraphic, rocketBehavior, 15, 21);
		addObject(*rocket);
	}

	//Create Enemy pool
	enemy_pool.Create(50);
	enemyGraphic = new EnemyGraphicComponent(system);
	for (auto enemy = enemy_pool.pool.begin(); enemy != enemy_pool.pool.end(); enemy++) {
		(*enemy)->create(enemyGraphic,28,35,globalListeners);
		std::vector<Component*> *componentListeners = (*enemy)->getListeners();
		EnemyBehaviorComponent *EnemyBeaviorComponent = new EnemyBehaviorComponent((*enemy),&enemy_rocket_pool, componentListeners,globalListeners);
		addObject(*enemy);
		(*enemy)->addComponentUpdaters(EnemyBeaviorComponent);
	}

	//Create Item pool
	item_pool.Create(10);
	itemGrapicComponent = new ItemGraphicComponent(system);
	for (auto item = item_pool.pool.begin(); item != item_pool.pool.end(); item++) {
		(*item)->create(system, globalListeners);
		addObject(*item);
		(*item)->setRenderComponent(itemGrapicComponent);
		itemBehaviourComponent *itemBehaviorComponent = new itemBehaviourComponent((*item));
		(*item)->addComponentUpdaters(itemBehaviorComponent);
	}

	levelSpawner = new LevelSpawner(&enemy_pool, &item_pool);
	globalListeners->push_back(levelSpawner);
}

void World::init()
{
	player->init(windowWidth / 2, windowHeight - 32);
	levelSpawner->init();
	scoreHandler->resetScore();
	gameStatus = CONTINUE;
}

void World::addObject(GameObject * object)
{
	game_objects.push_back(object);
}


void World::spawnEnemy(int x, int y) {
	Enemy * enemy = enemy_pool.FirstAvailable();
	if (enemy != NULL)	// rocket is NULL is the object pool can not provide an object
	{
		enemy->init(x, y);
	}
}

void World::collistionDetection() {

	if (player->enabled) {
		int playerHeight = player->getHeight();
		int playerWidth = player->getWidth();
		int playerX = player->getX();
		int playerY = player->getY();
		//Check Player against Enemies
		int enemyHeight;
		int enemyWidth;
		int enemyX, enemyY;

		int playerRocketX, playerRocketY;
		int playerRocketWidth;
		int playerRocketHeight;
		for (auto enemy = enemy_pool.pool.begin(); enemy != enemy_pool.pool.end(); enemy++) {
			if ((*enemy)->enabled) {
				enemyHeight = (*enemy)->getHeight();
				enemyWidth = (*enemy)->getWidth();
				enemyX = (*enemy)->getX();
				enemyY = (*enemy)->getY();
				if (checkCollision(playerX, playerY, playerWidth, playerHeight, enemyX, enemyY, enemyWidth, enemyHeight)) {
					player->Receive(HIT);
					(*enemy)->Receive(HIT);
				}
				//and Check Player Rockets against the enemy
				for (auto playerRocket = player_rocket_pool.pool.begin(); playerRocket != player_rocket_pool.pool.end(); playerRocket++) {
					if ((*playerRocket)->enabled) {
						playerRocketX = (*playerRocket)->getX();
						playerRocketY = (*playerRocket)->getY();
						playerRocketWidth = (*playerRocket)->getWidth();
						playerRocketHeight = (*playerRocket)->getHeight();
						if (checkCollision(playerRocketX, playerRocketY, playerRocketWidth, playerRocketHeight, enemyX, enemyY, enemyWidth, enemyHeight)) {
							(*playerRocket)->Receive(HIT);
							(*enemy)->Receive(HIT);
						}
					}
				}
				//and Check Player Missile against the enemy
				for (auto playerRocket = player_missile_pool.pool.begin(); playerRocket != player_missile_pool.pool.end(); playerRocket++) {
					if ((*playerRocket)->enabled) {
						playerRocketX = (*playerRocket)->getX();
						playerRocketY = (*playerRocket)->getY();
						playerRocketWidth = (*playerRocket)->getWidth();
						playerRocketHeight = (*playerRocket)->getHeight();
						if (checkCollision(playerRocketX, playerRocketY, playerRocketWidth, playerRocketHeight, enemyX, enemyY, enemyWidth, enemyHeight)) {
							(*playerRocket)->Receive(HIT);
							(*enemy)->Receive(HIT_MISSILE);
						}
					}
				}
			}

		}
		//Check Player against Enemy missiles
		for (auto enemyRocket = enemy_rocket_pool.pool.begin(); enemyRocket != enemy_rocket_pool.pool.end(); enemyRocket++) {
			if ((*enemyRocket)->enabled) {
				enemyHeight = (*enemyRocket)->getHeight();
				enemyWidth = (*enemyRocket)->getWidth();
				enemyX = (*enemyRocket)->getX();
				enemyY = (*enemyRocket)->getY();
				if (checkCollision(playerX, playerY, playerWidth, playerHeight, enemyX, enemyY, enemyWidth, enemyHeight)) {
					player->Receive(HIT);
					(*enemyRocket)->Receive(HIT);
				}
			}
		}

		//Check player against power ups
		int itemHeight;
		int itemWidth;
		int itemX;
		int itemY;

		for (auto item = item_pool.pool.begin(); item != item_pool.pool.end(); item++) {
			if ((*item)->enabled) {
				itemHeight = (*item)->getHeight();
				itemWidth = (*item)->getWidth();
				itemX = (*item)->getX();
				itemY = (*item)->getY();
				if (checkCollision(playerX, playerY, playerWidth, playerHeight, itemX, itemY, itemWidth, itemHeight)) {
					(*item)->Receive(HIT);
					player->gainPowerUp((*item)->getItemType());
				}
			}
		}
	}
}

//This only works if x and y is at the center of the object
bool World::checkCollision(int object_x, int object_y, int objectWidth, int objectHeight, int other_x, int other_y, int otherWidth, int otherHeight) {
	
	//     "player" Left edge				"enemy" Right edge				"Player" Right edge			"Enemy" left edge
	if ( ((object_x - objectWidth/2) <= (other_x + otherWidth/2)) && ((object_x + objectWidth/2) >= other_x - otherWidth/2) ) {
		//Collision in x-axis ok! check Y axis
		
		//		P - Top							E - Bottom					P - Bottom					E - Top
		if (((object_y - objectHeight/2) <= (other_y + otherHeight/2) && ((object_y + objectHeight/2) >= other_y - otherHeight/2) )) {
			return true;
		}
	}
	return false;
}

void World::checkWinningCondition() {
	if (!player->enabled) {

		// Go back to menu
		gameStatus = START_MENU; 
		for (int i = 0; i < game_objects.size(); i++) { 
			game_objects[i]->enabled = false;
		}
	}
}

void World::playerInputs() {
	AvancezLib::KeyStatus key;
	system->getKeyStatus(key);
	if (key.pause) {
		pause = true;	
	}
	else pause = false;
}

void World::update() {
	playerInputs();
	if (!pause) {
		levelSpawner->update();
		collistionDetection();
		for (int i = 0; i < game_objects.size(); i++) {
			if (game_objects[i]->enabled) {
				game_objects[i]->update();
			}
		}	
	checkWinningCondition();
	}
}

void World::render() {
	if (!pause) {
		for (int i = 0; i < game_objects.size(); i++) {
			if (game_objects[i]->enabled) {
				game_objects[i]->render();
			}		
		}
		scoreHandler->update();
	}
}

//This is used to change the gamestate (Run menu or world etc..)
statusAction World::getStatus()
{
	return gameStatus;
}

void World::destroy() {

	delete missileGraphic;
	delete rocketGraphic;
	delete itemGrapicComponent;
	delete lifeBar;
	delete enemyRocketGraphic;
	delete enemyGraphic;
	delete scoreHandler;
	delete levelSpawner;

	for (int i = 0; i < game_objects.size(); i++) {
			game_objects[i]->destroy();		
	}

	player_pool.Destroy();
	enemy_pool.Destroy();
	player_rocket_pool.Destroy();
	player_missile_pool.Destroy();
	enemy_rocket_pool.Destroy();
	item_pool.Destroy();

	rocketSprite->destroy();
	rocketSprite = NULL;
	missileSprite->destroy();
	missileSprite = NULL;
	enemyRocketSprite->destroy();
	enemyRocketSprite = NULL;

	delete player;
	playerGraphicComponent->destroy();
	delete playerGraphicComponent;
}