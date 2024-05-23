#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
//#include <filesystem>
using namespace std;

const int height = 480;
const int width = 640;

class Ltexture 
{
public:
		Ltexture();
		~Ltexture();

		bool loadmedia(string path);

		void free();
		void render(int x, int y,SDL_Rect* clip=NULL);

		int getwidth();
		int getheight();

private:
	SDL_Texture* texture;

	int imageheight;
	int imagewidth;

};


bool init();
bool load();
void close();
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect SpriteClips[4];
Ltexture spritesheettexture;


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

bool Ltexture::loadmedia(string path)
{
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedsurface = IMG_Load(path.c_str());
	if (loadedsurface == NULL)
	{
		printf("error1");

	}
	else
	{
		SDL_SetColorKey(loadedsurface, SDL_TRUE, SDL_MapRGB(loadedsurface->format, 0, 0xff, 0xff));

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedsurface);
		if (newTexture == NULL)
		{
			printf("error2");

		}
		else 
		{
			imagewidth = loadedsurface->w;
		    imageheight = loadedsurface->h;
		}
		SDL_FreeSurface(loadedsurface);
	}

	texture = newTexture;
	return texture != NULL;
}

void Ltexture::free() 
{
	if (texture == NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		imagewidth =0;
		imageheight = 0;

	}
}

void Ltexture::render(int x, int y,SDL_Rect*clip)
{
	SDL_Rect quad = { x,y,imagewidth,imageheight };
	if (clip != NULL)
	{
		quad.w = clip->w;
		quad.h = clip->h;
	}
	SDL_RenderCopy(renderer, texture, clip, &quad);
}

int Ltexture::getwidth()
{
	return imagewidth;
}

int Ltexture::getheight()
{
	return imageheight;
}
bool init()
	{
	bool success = true ;

	window = SDL_CreateWindow("Spandan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("error3");

	}
	else
	{
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			printf("error4");

		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff,0xff);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				printf("error5");
				success = false;
			}
		}
	}
	return success;

	}

bool load()
{
	bool success = true;
	if (!spritesheettexture.loadmedia("C:/Users/spand/source/repos/SDL/SDL/dots.png"))
	{
		printf("error6");

	}
	else
	{
		SpriteClips[0].x = 0;
		SpriteClips[0].y = 0;
		SpriteClips[0].w = 100;
		SpriteClips[0].h = 100;

		//Set top right sprite
		SpriteClips[1].x = 100;
		SpriteClips[1].y = 0;
		SpriteClips[1].w = 100;
		SpriteClips[1].h = 100;

		//Set bottom left sprite
		SpriteClips[2].x = 0;
		SpriteClips[2].y = 100;
		SpriteClips[2].w = 100;
		SpriteClips[2].h = 100;

		//Set bottom right sprite
		SpriteClips[3].x = 100;
		SpriteClips[3].y = 100;
		SpriteClips[3].w = 100;
	    SpriteClips[3].h = 100;
	}

	
	/*if (!bgimage.loadmedia("C:/Users/spand/source/repos/SDL/SDL/background.png"))
	{
		printf("error7");

	}*/
	return success;
}

void close()
{
	;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;


	IMG_Quit();
	SDL_Quit();

}
int main(int argc, char* args[])
{
	if (!init())
	{
		printf("error8");
	}
	else
	{
		if (!load())
		{
			printf("error9");
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT) 
					{
						quit = true;
					}
				}
				SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
				SDL_RenderClear(renderer);
				spritesheettexture.render(0, 0, &SpriteClips[0]);
				spritesheettexture.render(width-SpriteClips[1].w, 0, &SpriteClips[1]);

				spritesheettexture.render(0, height-SpriteClips[2].h, &SpriteClips[2]);
				spritesheettexture.render(width - SpriteClips[3].w , height - SpriteClips[3].h, &SpriteClips[3]);


				
				SDL_RenderPresent(renderer);

			}



		}
	}
	close();
	return 0;

}
