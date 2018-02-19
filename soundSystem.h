#pragma once
#pragma once
#include "observer.h"
#include "avancezlib.h"
class SoundSystem : public Observer {
public:
	SoundSystem(AvancezLib *system);
	
	void receive(Message_Observers msg);
	void destroy();

private:
	AvancezLib *system;
	Mix_Chunk *laser;
	Mix_Chunk *shieldhit;
	Mix_Chunk *die;
	Mix_Chunk *enemyHit;
	Mix_Chunk *slowLaser;
	Mix_Chunk *menuChange;
	Mix_Chunk *menuSelect;
	Mix_Chunk *gain_hp;
	Mix_Chunk *power_up;
	Mix_Chunk *gain_rocket;
	Mix_Chunk *fire_missile;
};