#include "scoreHandler.h"
#include "SystemSpecifications.h"
#include <string.h>
#include <sstream>

ScoreHandler::ScoreHandler(AvancezLib * system)
{
	this->system = system;
}

void ScoreHandler::update()
{
	std::string s = std::to_string(score);
	const char *points = s.c_str();
	const char *text = "Score:   ";
	system->drawText(windowWidth / 2 - 50, 20, text);
	system->drawText(windowWidth / 2 - 0, 20, points);

	s = std::to_string(highScore);
	const char *highScorepoints = s.c_str();
	const char *highScoreText = "High Score:   ";
	system->drawText(windowWidth / 2 - 90, 0, highScoreText);
	system->drawText(windowWidth / 2 + 0, 0, highScorepoints);

}

void ScoreHandler::addScore(int scoreToAdd)
{
	score = score + scoreToAdd;
	if (score % 100 == 0) {
	}
}

int ScoreHandler::getScore()
{
	return score;
}

int ScoreHandler::getHighScore()
{
	return 0;
}

void ScoreHandler::resetScore()
{
	if (highScore < score) {
		highScore = score;
	}
	score = 0;
}

void ScoreHandler::receive(Message_Observers msg)
{
	if (msg == ENEMY_KILLED) {
		addScore(10);
	}
}

void ScoreHandler::destroy()
{
}
