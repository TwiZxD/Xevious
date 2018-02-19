#include "soundSystem.h"

SoundSystem::SoundSystem(AvancezLib * system)
{
	this->system = system;

	laser = system->createSound("res/sound/laser.wav");
	shieldhit = system->createSound("res/sound/jump.wav");
	die = system->createSound("res/sound/die.wav");
	enemyHit = system->createSound("res/sound/boing.wav");
	slowLaser = system->createSound("res/sound/slowlaser.wav");
	menuChange = system->createSound("res/sound/menuChange.wav");
	menuSelect = system->createSound("res/sound/game_start_ogg.wav");
	gain_hp = system->createSound("res/sound/health_up.wav");
	power_up = system->createSound("res/sound/power_up.wav");
	gain_rocket = system->createSound("res/sound/reload_space.wav");
	fire_missile = system->createSound("res/sound/missile_fire.wav");

}

void SoundSystem::receive(Message_Observers msg)
{
	switch (msg) {
	case MENU_CHANGE:
		Mix_PlayChannel(-1, menuChange, 0);
		break;
	case MENU_SELECT:
		Mix_PlayChannel(-1, menuSelect, 0);
		break;
	case PLAY_GAIN_HP:
		Mix_PlayChannel(-1, gain_hp, 0);
		break;
	case PLAY_POWER_UP:
		Mix_PlayChannel(-1, power_up, 0);
		break;
	case PLAY_GAIN_ROCKET:
		Mix_PlayChannel(-1, gain_rocket, 0);
		break;
	case PLAYLASER:
		Mix_PlayChannel(-1, laser, 0);
		break;
	case PLAY_SHIELD_HIT:
		Mix_PlayChannel(-1, shieldhit, 0);
		break;
	case PLAY_DIE:
		Mix_PlayChannel(-1, die, 0);
		break;
	case PLAY_ENEMY_HIT:
		Mix_PlayChannel(-1, enemyHit, 0);
		break;
	case PLAY_ENEMY_FIRE:
		Mix_PlayChannel(-1, slowLaser, 0);
		break;
	case PLAY_MISSILE_FIRE:
		Mix_PlayChannel(-1, fire_missile, 0);
		break;
	}


}

void SoundSystem::destroy()
{
	system->deleteSound(laser);
	system->deleteSound(shieldhit);
	system->deleteSound(die);
	system->deleteSound(enemyHit);
	system->deleteSound(slowLaser);
	system->deleteSound(menuChange);
	system->deleteSound(menuSelect);
	system->deleteSound(gain_hp);
	system->deleteSound(power_up);
	system->deleteSound(gain_rocket);
	system->deleteSound(fire_missile);
}
