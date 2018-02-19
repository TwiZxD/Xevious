#define _CRT_SECURE_NO_WARNINGS
#include "SDL.h"
#include "avancezlib.h"
#include <stdio.h>
#include <iostream>
#include "world.h"
#include "SystemSpecifications.h"
#include "menuScreen.h"
#include "observer.h"
#include "soundSystem.h"
#include "scoreHandler.h"
bool running = false;
int MS_PER_FRAME = 16;
int amountOfPlayers = 1;
char *title;
char *titleText = "Xevious";

std::vector<Observer*> globalListeners;
GameState *state;



int main(int argc, char* argv[])
{	
	AvancezLib system;

	title = titleText;
	char msg[256] = "Calculating...";
	
	bool gameRunning = system.init(windowWidth, windowHeight, title);

	SoundSystem sound(&system);
	globalListeners.push_back(&sound);

	World world(&system, &globalListeners);

	MenuScreen menu(&system, &globalListeners);
	state = &menu; 


	int timeBefore = system.getElapsedTime();
	int delta = 0;
	int now = system.getElapsedTime();

	//FPS Display
	int framesPerSecond = 0;
	int updatesPerSecond = 0;
	int timer = system.getElapsedTime();

	//Game Loop
	while (gameRunning) {
		now = system.getElapsedTime();
		delta += (now - timeBefore);
		timeBefore = now;

		//Update fuction
		while (gameRunning && delta >= MS_PER_FRAME) {
			delta -= MS_PER_FRAME;
			updatesPerSecond++;
			gameRunning = system.inputHandler();
			
			//Select GameState
			switch(state->getStatus()){
			case ONE_PLAYER:
				amountOfPlayers = 1;
				state->init();
				state = &world;
				break;
			case TWO_PLAYER:
				amountOfPlayers = 2;
				state->init();
				state = &world;
				break;
			case CONTINUE:
				//continue...
				break;
			case START_MENU:
				state->init();
				state = &menu;
				break;
			case QUIT:
				gameRunning = false;
				break;
			default:
				//do nothing...
				break;
			}

			state->update(); //update world or menu
			state->render(); //render world or menu
			system.update();		
		}

		framesPerSecond++;
		if (system.getElapsedTime() - timer > 1000) {
			timer += 1000;

			sprintf(msg, "UPS: %i, FPS: %i", updatesPerSecond, framesPerSecond);
			sprintf(msg, "UPS: %i    FPS: %i", updatesPerSecond, framesPerSecond);
			updatesPerSecond = 0;
			framesPerSecond = 0;

			system.setTitle(msg);
		}
	}
	
	for (auto i = 0; i < globalListeners.size(); i++)
	{
		if (globalListeners[i] != NULL) {
			globalListeners[i]->destroy();
		}
	}
	world.destroy();
	menu.destroy();
	system.destroy();
	return 0;
}

