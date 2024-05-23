#include <iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
using namespace std;
const int height = 480;
const int width = 640;

class Ltexture
{
public:
	Ltexture();
	~Ltexture();
	bool loadfile(string path);
	void render(int x, int y);
	void free();
	
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setblendmode(SDL_BlendMode blend);
	void setalpha(Uint8 alpha);
	int getheight();
	int getwidth();

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
Ltexture image;
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

void Ltexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
}

void Ltexture::setblendmode(SDL_BlendMode blend)
{
	SDL_SetTextureBlendMode(texture ,blend);
}

void Ltexture::setalpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}
bool Ltexture::loadfile(string path)
{
	free();
	SDL_Texture* Newtexture = NULL;
	SDL_Surface* Loadedsurface = IMG_Load(path.c_str());
	if (Loadedsurface == NULL)
	{
		printf("error1");
	}
	else
	{
		SDL_SetColorKey(Loadedsurface, SDL_TRUE, SDL_MapRGB(Loadedsurface->format, 0xff, 0xff, 0xff));
		Newtexture = SDL_CreateTextureFromSurface(renderer,Loadedsurface);
		if (Loadedsurface == NULL)
		{
			printf("error2");

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
	SDL_Rect quad = { x, y, imagewidth, imageheight };
	SDL_RenderCopy(renderer, texture, NULL, &quad);
}

int Ltexture::getheight() 
{
	return imageheight;
}
int Ltexture::getwidth()
{
	return imagewidth;
}

bool init()
{
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

		window = SDL_CreateWindow("spandan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("error3");
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("error3");
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

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
	bool success = true;
	if (!image.loadfile("C:/Users/spand/source/repos/SDL/SDL/fadeout.png"))
	{
		printf("error");
		success = false;
	}
	else
	{
		image.setblendmode(SDL_BLENDMODE_BLEND);
	}

	if (!bgimage.loadfile("C:/Users/spand/source/repos/SDL/SDL/fadein.png"))
	{
		printf("error");
	}
	else
	{
		bgimage.setblendmode(SDL_BLENDMODE_BLEND);
	}
	return success;

	}

void close()
{
	image.free();
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
			int a = 255;
			int b = 0;
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
						if (e.key.keysym.sym == SDLK_w) 
						{
							if (b + 32 > 255)
							{
								b = 255;
							}
							else
							{
								b += 32;
							}
						}
						else if (e.key.keysym.sym == SDLK_a)
						{
							if (b - 32 < 0)
							{
								b = 0;

							}
							else
							{
								b -= 32;
							}
						}
						else if (e.key.keysym.sym == SDLK_s)
						{
							if (a - 32 < 0)
							{
								a = 0;

							}
							else
							{
								a -= 32;
							}
						}
						else if (e.key.keysym.sym == SDLK_d)
						{
							if (a + 32 > 255)
							{
								a = 255;
							}
							else
							{
								a += 32;
							}
						}
					}

					SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
					SDL_RenderClear(renderer);
					bgimage.setalpha(b);
					bgimage.render(0, 0);
					image.setalpha(a);
					image.render(0, 0);


					
					SDL_RenderPresent(renderer);
				}
			}
		}
	}
	close();
	return 0;
}