#ifndef __AVANCEZ_LIB__
#define __AVANCEZ_LIB__

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
class Sprite
{
	SDL_Renderer * renderer;
	SDL_Texture * texture;


public:

	Sprite(SDL_Renderer * renderer, SDL_Texture * texture);

	// Destroys the sprite instance
	void destroy();

	int getWidth();

	// Draw the sprite at the given position.
	// Valid coordinates are between (0,0) (upper left) and (width-32, height-32) (lower right).
	// (All sprites are 32*32 pixels, clipping is not supported)
	void draw(int x, int y);
};


class AvancezLib
{


public:
	// Destroys the avancez library instance
	void destroy();

	// Creates the main window. Returns true on success.
	bool init(int width, int height, char *title);

	// Clears the screen and draws all sprites and texts which have been drawn
	// since the last update call.
	// If update returns false, the application should terminate.
	void update();

	Mix_Chunk* createSound(const char * path);

	void deleteSound(Mix_Chunk * chunk);

	void render();
	// Create a sprite given a string.
	// All sprites are 32*32 pixels.
	Sprite* createSprite(const char* name);

	// Draws the given text.
	void drawText(int x, int y, const char* msg);
	//void drawText(int x, int y);

	void setTitle(char *title);

	// Return the total time spent in the game, in seconds.
	int getElapsedTime();

	struct KeyStatus
	{
		bool fire; // space
		bool left = false; // left arrow
		bool right = false; // right arrow
		bool up = false; // right arrow
		bool down = false; // right arrow
		bool pause = false;
	};

	bool inputHandler();

	// Returns the keyboard status. If a flag is set, the corresponding key is being held down.
	void getKeyStatus(KeyStatus& keys);

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	TTF_Font* font;
	KeyStatus key;
};





#endif // __AVANCEZ_LIB__
