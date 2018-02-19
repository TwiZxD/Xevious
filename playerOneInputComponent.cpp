#include "playerOneInputComponent.h"
PlayerOneInputController::PlayerOneInputController(AvancezLib *system, std::vector<Component*>* receivers) {
	this->system = system;
	this->receivers = receivers;
}
void PlayerOneInputController::update()
{
	AvancezLib::KeyStatus key;
	system->getKeyStatus(key);
	if (key.fire) {
		Send(INPUT_SPACE);
	}
	if (key.left) {
		Send(INPUT_LEFT);
	}
	else if (key.right) {
		Send(INPUT_RIGHT);
	}
	if (key.up) {
		Send(INPUT_UP);
	}
	else if (key.down) {
		Send(INPUT_DOWN);
	}
	
}

void PlayerOneInputController::Send(Message m)
{
	for (auto i = 0; i < receivers->size(); i++)
	{
		receivers->at(i)->receive(m);
	}
}

