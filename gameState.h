#pragma once
enum statusAction {CONTINUE, START_MENU, START_GAME, ONE_PLAYER, TWO_PLAYER, QUIT};
class GameState {
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void init() = 0;
	virtual statusAction getStatus() = 0;
};