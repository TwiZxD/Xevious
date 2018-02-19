#pragma once
#include "SDL.h"

enum Message2 { HIT, ALIEN_HIT, HIT_MISSILE};
class GameObject
{
public:
	GameObject();
	virtual ~GameObject() {}
	virtual void update() = 0;
	virtual void render() = 0;
	virtual int getX() const { return x_; }
	virtual int getY() const { return y_; }
	void setX(int x) { x_ = x; }
	void setY(int y) { y_ = y; }
	virtual int getWidth() const { return width; }
	virtual int getHeight() const { return height; }
	virtual void setWidth(int width) { this->width = width; }
	virtual void setHeight(int height) { this->height = height; }

	virtual void Receive(Message2 m) {}
	virtual void destroy() {};
	bool enabled;

private:
	int x_;
	int y_;
	int width;
	int height;
};