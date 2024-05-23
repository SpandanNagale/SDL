#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
using namespace std;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Ltexture
{
public:
	Ltexture();
	~Ltexture();
	bool Loadfile(string path);
	void free();
	void render(int x, int y);
	int getimageheight();
	int getimagewidth();
private:
	SDL_Texture* texture;
	int imageheight;
	int imagewidth;
};

bool init();
bool loadmedia();
void close();
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
Ltexture foo;
Ltexture bgimage;

Ltexture::Ltexture()
{
	texture = NULL;
   imageheight = 0;
    imagewidth = 0;


}

Ltexture::~Ltexture()
{
	free();
}

bool Ltexture:: Loadfile(string path)
{
	free();

	SDL_Texture* Newtexture = NULL;
	SDL_Surface* Loadedsurface = IMG_Load(path.c_str());
	if (Loadedsurface == NULL)
	{
		printf("error");

	}
	else
	{
		SDL_SetColorKey(Loadedsurface, SDL_TRUE, SDL_MapRGB(Loadedsurface->format, 0, 0xff, 0xff));
		Newtexture = SDL_CreateTextureFromSurface(renderer, Loadedsurface);
		if (Newtexture == NULL) 
		{
			printf("error");
		}
		else
		{
			imageheight = Loadedsurface->h;
			imagewidth = Loadedsurface->w;
		}
		SDL_FreeSurface(Loadedsurface);
	}
	texture = Newtexture;
	return texture != NULL;
}

void Ltexture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		imageheight = 0;
		imagewidth = 0;
	}
}

void Ltexture::render(int x, int y)
{
	SDL_Rect quad = { x,y,imagewidth,imageheight };
	SDL_RenderCopy(renderer, texture, NULL, &quad);
}

int Ltexture::getimageheight() 
{
	return imageheight;
}
int Ltexture::getimagewidth()
{
	return imagewidth;
}
bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadmedia()
{   
	bool success=true;

	if (!foo.Loadfile("C:/Users/spand/source/repos/SDL/SDL/foo.png"))
	{
		printf("error");
		success = false;
	}
	
	if (!bgimage.Loadfile("C:/Users/spand/source/repos/SDL/SDL/background.png"))
	{
		printf("error");
		success = false;
	}
	return success;
}

void close()
{
	foo.free();
	bgimage.free();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	SDL_Quit();
	IMG_Quit();

}

int main(int argc, char* args[])
{
	if (!init())
	{
		printf("error");
	}
	else
	{
		if (!loadmedia())
		{
			printf("error");

		}
		else
		{
			bool quit = false;
			SDL_Event e;
			int h=190;
			int w=240;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					else if (e.type = SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							h -= 30;
							break;
						case SDLK_DOWN:
							h += 30;
							break;
						case SDLK_RIGHT:
							w += 30;
							break;
						case SDLK_LEFT:
							w -= 30;
							break;
						default:
							break;
						}
					}
				}

				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff,0xff);
				SDL_RenderClear(renderer);

				bgimage.render(0, 0);
				foo.render(w, h);

				SDL_RenderPresent(renderer);
			}

		}
	}
	close();

	return 0;
}
