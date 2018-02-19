#pragma once
#include "object_pool.h"
enum Message { INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT, INPUT_FIRE,
	SPRITE_LEFT, SPRITE_RIGHT, SPRITE_UP, SPRITE_DOWN, INPUT_SPACE,
	};

class Component {
public:
	virtual void update() {};
	virtual void receive(Message msg) {}
	virtual void destroy() {};
};