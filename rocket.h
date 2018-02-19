#pragma once
#include "components.h"
#include "gameObject.h"
#include "basicGraphicComponent.h"

class Rocket : public GameObject {
public :
	Rocket();
	void create(BasicGraphicComponent *graphicComponent,Component *behaviourComponent, int width, int height);
	void update();
	void init(int x, int y);
	void render();
	void Receive(Message2 msg);
	void destroy();
	
private:
	BasicGraphicComponent *graphicComponent;
	Component *behaviourComponent;
	int timeToLive;
};
