#include "rocket.h"

Rocket::Rocket()
{
}

void Rocket::create(BasicGraphicComponent * graphicComponent, Component *behaviourComponent, int width, int height) {
	this->graphicComponent = graphicComponent;
	this->behaviourComponent = behaviourComponent;
	setWidth(width);
	setHeight(height);
}
void Rocket::update() {
	behaviourComponent->update();
	timeToLive--;
	if (getY() <= 0 || timeToLive <= 0) {
		enabled = false;
	}
}

void Rocket::init(int x, int y) {
	setX(x);
	setY(y);
	enabled = true;
	timeToLive = 150;
}

void Rocket::render() {
	if (enabled) {
		graphicComponent->render(getX(), getY());
	}
}


void Rocket::Receive(Message2 msg)
{
	if (msg == HIT) {
		enabled = false;
	}
}

void Rocket::destroy() {
	if(behaviourComponent != NULL){
		delete behaviourComponent;
		behaviourComponent = NULL;
	}
	
}