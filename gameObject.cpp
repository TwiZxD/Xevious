#include "gameObject.h"
GameObject::GameObject() {
	this->x_ = 0;
	this->y_ = 0;
	this->width = 1;
	this->height = 1;
	enabled = false;
}
//GameObject::GameObject(int x, int y) {
//	this->x_ = x;
//	this->y_ = y;
//	this->width = 1;
//	this->height = 1;
//	enabled = false;
//}
//
//GameObject::GameObject(int x, int y, int width, int height) {
//	this->x_ = x;
//	this->y_ = y;
//	this->width = width;
//	this->height = height;
//	enabled = false;
//}
//GameObject::GameObject(int x, int y, int spriteWidth, int spriteHeight, int hitBoxWidth, int hitBoxHeight)
//{
//	this->x_ = x;
//	this->y_ = y;
//	this->width = spriteWidth;
//	this->height = spriteHeight;
//	this->hitBoxHeight = hitBoxHeight;
//	this->hitBoxWidth = hitBoxWidth;
//	enabled = false;
//}
void GameObject::update() {
	SDL_Log("Update in GameObject");
}

