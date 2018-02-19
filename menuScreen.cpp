#include "menuScreen.h"

MenuScreen::MenuScreen(AvancezLib * system, std::vector<Observer*> *globalListeners)
{
	this->system = system;
	this->globalListeners = globalListeners;
	xevious_Sprite = system->createSprite("res/Xevious_Title.png");
}

void MenuScreen::init() {
	status = CONTINUE;
}
void MenuScreen::playerInputs() {
	AvancezLib::KeyStatus key;
	system->getKeyStatus(key);
	if (key.fire) {
		selectItem();
	}
	if (key.up) {
		upPressed = true;
	} else if (upPressed) {
		goUp();
		upPressed = false;
	}
	if (key.down) {
		downPressed = true;
	} else if (downPressed) {
		goDown();
		downPressed = false;
	}
}

void MenuScreen::goDown() {
	menuSelect++;
	if (menuSelect > 2) menuSelect = 2;
	else send(MENU_CHANGE);
}

void MenuScreen::goUp() {
	menuSelect--;
	if (menuSelect < 0) menuSelect = 0;
	else send(MENU_CHANGE);
}

void MenuScreen::selectItem() {
	send(MENU_SELECT);
	switch (menuSelect) {
	case 0:
		status = ONE_PLAYER;
		break;
	case 1:
	//	status = TWO_PLAYER;
		break;
	case 2:
		status = QUIT;
		break;
	default:
		status = CONTINUE;
		break;
	}
}

statusAction MenuScreen::getStatus() {
	return status;
}

void MenuScreen::update()
{
	playerInputs();
}

void MenuScreen::render()
{
	xevious_Sprite->draw(windowWidth / 2 , windowHeight / 2);
	system->drawText(windowWidth / 2 - 40, windowHeight / 2 + 100 + 20 * menuSelect, ">");

	system->drawText(windowWidth / 2 - 30, windowHeight / 2 + 100, "Player 1");
	system->drawText(windowWidth / 2 - 30, windowHeight / 2 + 120, "Player 2   ( Coming soon.. )");
	system->drawText(windowWidth / 2 - 30, windowHeight / 2 + 140, "Quit Game");

	system->drawText(windowWidth / 2 - 60, windowHeight - 50, "  @ Johan Segerlund");
}

void MenuScreen::send(Message_Observers m)
{
	for (auto i = 0; i < globalListeners->size(); i++)
	{
		globalListeners->at(i)->receive(m);
	}
}

void MenuScreen::destroy()
{
	if (xevious_Sprite != NULL)
		xevious_Sprite->destroy();
	xevious_Sprite = NULL;
}
