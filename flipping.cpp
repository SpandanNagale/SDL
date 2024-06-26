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
	void render(int x, int y,SDL_Rect* clip = NULL, double angle=0.0, SDL_Point*center=NULL,SDL_RendererFlip flip=SDL_FLIP_NONE );
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
	SDL_SetTextureBlendMode(texture, blend);
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
		Newtexture = SDL_CreateTextureFromSurface(renderer, Loadedsurface);
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

void Ltexture::render(int x, int y ,SDL_Rect*clip,double angle,SDL_Point*center,SDL_RendererFlip flip)
{
	SDL_Rect quad = { x, y, imagewidth, imageheight };
	if (clip != NULL)
	{
		quad.w = clip->w;
		quad.h = clip->h;

	}
	SDL_RenderCopyEx(renderer, texture, clip, &quad,angle,center,flip);
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
	if(!image.loadfile("C:/Users/spand/source/repos/SDL/SDL/arrow.png"))
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
			double degree = 0;
			SDL_RendererFlip fliptype = SDL_FLIP_NONE;
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
						case SDLK_a:
							degree -= 60;
							break;

						case SDLK_d:
							degree += 60;
							break;
						case SDLK_w:
							fliptype = SDL_FLIP_NONE;
							break;
						case SDLK_q:
							fliptype = SDL_FLIP_HORIZONTAL;
							break;
						case SDLK_e:
							fliptype = SDL_FLIP_VERTICAL;
							break;
						}
					}
				}

					SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
					SDL_RenderClear(renderer);
					
					image.render((width - image.getwidth()) / 2, (height - image.getheight()) / 2, NULL, degree, NULL, fliptype);


					SDL_RenderPresent(renderer);
				
			}
		}
	}
	close();
	return 0;
}