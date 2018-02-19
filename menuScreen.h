#pragma once
#include "avancezlib.h"
#include "gameState.h"
#include "SystemSpecifications.h"
#include "observer.h"


class MenuScreen : public GameState {
public:
	MenuScreen(AvancezLib *system, std::vector<Observer*> *globalListeners);
	void playerInputs();
	statusAction getStatus();
	void init();
	void update();
	void render();
	void send(Message_Observers m);
	void destroy();
private:
	std::vector<Observer*> *globalListeners;

	void goDown();
	void goUp();
	void selectItem();

	AvancezLib * system;
	Sprite * xevious_Sprite;
	statusAction status;
	int menuSelect = 0;
	bool upPressed = false;
	bool downPressed = false;
};