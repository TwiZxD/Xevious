#pragma once
#include "playerGraphicComponent.h"


Sprite *player_left_halfspeed;
Sprite *player_front_halfspeed;
Sprite *player_right_halfspeed;

Sprite *player_left_nospeed;
Sprite *player_front_nospeed;
Sprite *player_right_nospeed;

Sprite *player_left_fullspeed;
Sprite *player_front_fullspeed;
Sprite *player_right_fullspeed;

bool left;
bool right;
bool up;
bool down;


PlayerGraphicComponent::PlayerGraphicComponent(AvancezLib *system)
{
	left = false;
	right = false;
	up = false;
	down = false;

	player_left_halfspeed = system->createSprite("res/player_left_halfspeed.png");
	player_front_halfspeed = system->createSprite("res/player_front_halfspeed.png");
	player_right_halfspeed = system->createSprite("res/player_right_halfspeed.png");

	player_left_nospeed = system->createSprite("res/player_left_nospeed.png");
	player_front_nospeed = system->createSprite("res/player_front_nospeed.png");
	player_right_nospeed = system->createSprite("res/player_right_nospeed.png");

	player_left_fullspeed = system->createSprite("res/player_left_fullspeed.png");
	player_front_fullspeed = system->createSprite("res/player_front_fullspeed.png");
	player_right_fullspeed = system->createSprite("res/player_right_fullspeed.png");
}


void PlayerGraphicComponent::render(int x, int y)
{	
	Sprite *sprite;
	if (up == true) {
		if (left == true) {
			sprite = player_left_fullspeed;
		} else if (right) {
			sprite = player_right_fullspeed;
		} else
		sprite = player_front_fullspeed;
	} else if (down == true) {
		if (left) {
			sprite = player_left_nospeed;
		}  
		else if (right == true) {
			sprite = player_right_nospeed;
		} else 
		sprite = player_front_nospeed;
	} else {
		if (left == true) {
			sprite = player_left_halfspeed;
		} else if (right == true){
			sprite = player_right_halfspeed;
		} else {
			sprite = player_front_halfspeed;
		}
	}

	sprite->draw(x, y);
	left = false;
	right = false;
	up = false;
	down = false;
}


void PlayerGraphicComponent::destroy()
{
	player_left_halfspeed->destroy();
	player_front_halfspeed->destroy();
	player_right_halfspeed->destroy();

	player_left_nospeed->destroy();
	player_front_nospeed->destroy();
	player_right_nospeed->destroy();

	player_left_fullspeed->destroy();
	player_front_fullspeed->destroy();
	player_right_fullspeed->destroy();
}

void PlayerGraphicComponent::receive(Message msg) {
	if (msg == INPUT_UP) {
		up = true;
	}
	else if (msg == INPUT_DOWN) {
		down = true;
	}
	if (msg == INPUT_LEFT) {
		left = true;
	}
	else if (msg == INPUT_RIGHT) {
		right = true;
	}
}
