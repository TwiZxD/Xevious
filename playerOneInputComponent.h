#pragma once
#include "components.h"
#include "avancezlib.h"

class PlayerOneInputController : public Component {
public:
	PlayerOneInputController(AvancezLib *system, std::vector<Component*> *receivers);
	void Send(Message m);
	void update();
private:
	AvancezLib *system;
	std::vector<Component*> *receivers;
};