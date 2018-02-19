#include "avancezlib.h"
#include <iostream>
#include <stdio.h>

void AvancezLib::destroy(){
	SDL_Log("Shutting down the system\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_CloseFont(font);
	
	TTF_Quit();
	SDL_Quit();
}

bool AvancezLib::init(int width, int height, char *title) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL failed the initialization: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//TTF init
	TTF_Init();

	font = TTF_OpenFont("space_invaders.ttf", 12);
	if (font == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 10, 10, 10, 0);

	//Clear screen
	SDL_RenderClear(renderer);

	// Inilialize SDL_mixer , exit if fail
	if (SDL_Init(SDL_INIT_AUDIO) < 0) exit(1);
	// Setup audio mode
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

	SDL_Log("System up and running...\n");
	return true;

}

void AvancezLib::update() {
	SDL_RenderPresent(renderer); //Update Screen
	SDL_RenderClear(renderer); //Clear Screen
}

Mix_Chunk* AvancezLib::createSound(const char* path) {
	Mix_Chunk * chunk = Mix_LoadWAV(path);
	if (chunk == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create sound from %s SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	return chunk;
}

void AvancezLib::deleteSound(Mix_Chunk* chunk) {
	Mix_FreeChunk(chunk);
}

Sprite * AvancezLib::createSprite(const char * path)
{
	SDL_Texture * texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	Sprite * sprite = new Sprite(renderer, texture);
	return sprite;
}


void AvancezLib::drawText(int x, int y, const char* msg) {
	SDL_Color black = { 255, 255, 255};
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, msg, black);
	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(renderer, textSurface); //now you can convert it into a texture

	int w = 0;
	int h = 0;
	SDL_QueryTexture(msg_texture, NULL, NULL, &w, &h);
	SDL_Rect dst_rect = { x, y, w, h };

	SDL_RenderCopy(renderer, msg_texture, NULL, &dst_rect);

	SDL_DestroyTexture(msg_texture);
	SDL_FreeSurface(textSurface);
}	

void AvancezLib::setTitle(char *title) {
	SDL_SetWindowTitle(window, title);
}
int AvancezLib::getElapsedTime() {
	return SDL_GetTicks();
}

bool AvancezLib::inputHandler() {
	SDL_Event event;
	bool go_on = true;

//	key.fire = false;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			go_on = false;
		}
		if (event.type == SDL_KEYDOWN)
		{
			SDL_Keycode keyPressed = event.key.keysym.sym;
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				go_on = false;
				break;
			case SDLK_q:
				go_on = false;
				break;
			case SDLK_SPACE:
				key.fire = true;
				break;
			case SDLK_LEFT:
				key.left = true;
				break;
			case SDLK_a:
				key.left = true;
				break;
			case SDLK_RIGHT:
				key.right = true;
				break;			
			case SDLK_DOWN:
				key.down = true;
				break;
			case SDLK_d:
				key.right = true;
				break;							
			case SDLK_w:
				key.up = true;
				break;
			case SDLK_UP:
				key.up = true;
				break;
			case SDLK_s:
				key.down = true;
				break;
			case SDLK_p:
				key.pause = true;
				break;
			}

		}
		if (event.type == SDL_KEYUP)
		{
			SDL_Keycode keyReleased = event.key.keysym.sym;
			switch (keyReleased)
			{
			case SDLK_a:
				key.left = false;
				break;
			case SDLK_LEFT:
				key.left = false;
				break;
			case SDLK_s:
				key.down = false;
				break;
			case SDLK_DOWN:
				key.down = false;
				break;
			case SDLK_d:
				key.right = false;
				break;
			case SDLK_RIGHT:
				key.right = false;
				break;
			case SDLK_w:
				key.up = false;
				break;
			case SDLK_UP:
				key.up = false;
				break;
			case SDLK_SPACE:
				key.fire = false;
				break;
			case SDLK_p:
				key.pause = false;
				break;
			}
		}	
	}
	return go_on;
}

void AvancezLib::getKeyStatus(KeyStatus& keys) {
	keys.fire = key.fire;
	keys.left = key.left;
	keys.right = key.right;
	keys.up = key.up;
	keys.down = key.down;
	keys.pause = key.pause;
}

Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture)
{
	this->renderer = renderer;
	this->texture = texture;
};

void Sprite::draw(int x, int y)
{
	SDL_Rect rect;

	SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &(rect.h));

	rect.x = x - (rect.w / 2);
	rect.y = y - (rect.h / 2);

	//Render texture to screen
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Sprite::destroy()
{	
	SDL_DestroyTexture(texture);
}
