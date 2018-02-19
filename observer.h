#pragma once
#include <vector>
enum Message_Observers {

	PLAYLASER, PLAY_SHIELD_HIT, PLAY_DIE, PLAY_ENEMY_HIT, PLAY_ENEMY_FIRE,
	PLAY_GAIN_HP, ENEMY_KILLED, PLAY_POWER_UP, PLAY_GAIN_ROCKET,
	MENU_CHANGE, MENU_SELECT, PLAY_MISSILE_FIRE
};


class Observer {
public:
	virtual void destroy() = 0;
	virtual void receive(Message_Observers msg) {};
	virtual void receive(Message_Observers msg,int x,int y) {};
};