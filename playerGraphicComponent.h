#pragma once
#include "components.h"
#include "avancezlib.h"
enum Input {UP, DOWN, LEFT, RIGHT };
class PlayerGraphicComponent : public Component{
public:
	PlayerGraphicComponent(AvancezLib *system);
	void render(int x, int y);
	void destroy();
	void receive(Message msg);
};