#pragma once
#pragma once
#include "observer.h"
#include "avancezlib.h"
#include "player.h"

class ScoreHandler : public Observer {
public:
	ScoreHandler(AvancezLib * system);
	void update();
	void addScore(int score);
	int getScore();
	int getHighScore();
	void resetScore();
	void receive(Message_Observers msg);
	void destroy();
private:
	int score;
	int highScore;
	AvancezLib * system;
	Player *player;
	int gainLevelTimer;
};