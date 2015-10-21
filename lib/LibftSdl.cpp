#include <iostream>
#include "LibftSdl.hpp"

SdlGraphics::SdlGraphics():
_name("Sdl Graphics")
{
	std::cout << "Sdl Graphic CREATION" << std::endl;
	if( SDL_Init( SDL_INIT_VIDEO ) == -1 )
    {
        std::cout << "Can't init SDL:  "<< SDL_GetError( ) << std::endl;
        exit(-1);
    }
    atexit( SDL_Quit );
    _window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );


    if ( _window == NULL)
    {
        std::cout << "Can't set video mode: "<< SDL_GetError( ) << std::endl;
        exit(-1);
    }
}

SdlGraphics::SdlGraphics(int x, int y):
_name("Sdl Graphics")
{
	std::cout << "Sdl Graphic CREATION" << std::endl;
	_width = x;
	_height = y;
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        std::cout << "Can't init SDL:  "<< SDL_GetError( ) << std::endl;
        exit(-1);
    }
    if(TTF_Init() == -1)
	{
    	fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    	exit(EXIT_FAILURE);
	}
    atexit( SDL_Quit );
    _window = SDL_CreateWindow(
        "Nibbler",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        x * CELL_SIZE + CELL_SIZE * 2,                               // width, in pixels
        y * CELL_SIZE + CELL_SIZE * 2 + CELL_SIZE,                               // height, in pixels
        SDL_WINDOW_BORDERLESS                 // flags - see below
    );

    if ( _window == NULL)
    {
        std::cout << "Can't set video mode: "<< SDL_GetError( ) << std::endl;
        exit(-1);
    }
    _Renderer = SDL_CreateRenderer(_window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE);
	if ( _Renderer )
	{
		_Twall = IMG_LoadTexture(_Renderer, "sprites/wall-2.bmp");
		_Tcorner = IMG_LoadTexture(_Renderer, "sprites/wall-corner-2.bmp");
		_Tapple = IMG_LoadTexture(_Renderer, "sprites/apple.png");
		_Tegg = IMG_LoadTexture(_Renderer, "sprites/egg.png");
		_rect.x = 0;
		_rect.y = 0;
		_rect.w = 32;
		_rect.h = 32;
    	_crop.x = 0;
		_crop.y = 0;
		_crop.w = 32;
		_crop.h = 32;
    	_center.x = 16;
		_center.y = 16;
	}
	_police = TTF_OpenFont("fonts/neuropolitical.ttf", 28);
}

SdlGraphics::SdlGraphics( SdlGraphics const & rhs )
{
	*this = rhs;
}

SdlGraphics::~SdlGraphics()
{
	std::cout << "Sdl Graphic DESTRUCTION" << std::endl;
	SDL_DestroyWindow(_window);
	TTF_CloseFont(_police);
	TTF_Quit();
	SDL_Quit();
}

SdlGraphics	*createGraphic( int w, int h )
{
	return new SdlGraphics(w, h);
}

void			deleteGraphic( SdlGraphics *graphic )
{
	delete graphic;
}

SdlGraphics &	SdlGraphics::operator=( SdlGraphics const & rhs )
{
	_name = rhs.getName();
	return *this;
}

std::string		SdlGraphics::getName( void ) const { return _name; }

void			SdlGraphics::clearScreen( void ) {
}

void			SdlGraphics::init( void ) const
{
	std::cout << _name << std::endl;
}

int				SdlGraphics::getInput( void )
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
    {
		switch(event.type){
			case SDL_QUIT:
				return (K_EX);
			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE :
						return (K_EX);
					case SDLK_UP:
						return (K_UP);
					case SDLK_DOWN:
						return (K_DW);
					case SDLK_LEFT:
						return (K_LT);
					case SDLK_RIGHT:
						return (K_RT);
					case SDLK_RETURN:
						return (K_CT);
					case SDLK_1:
						return (K_L1);
					case SDLK_2:
						return (K_L2);
					case SDLK_3:
						return (K_L3);
					default:
						return (0);
				}
			}
		}
	}
	return (0);
}

void SdlGraphics::drawCorners(void) {
	float angle = 0.0f;
	_rect.x = 0;
	_rect.y = 0;
	SDL_RenderCopyEx(_Renderer, _Tcorner, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);

	angle = 180.0f;
	_rect.x = _width * CELL_SIZE + CELL_SIZE;
	_rect.y = _height * CELL_SIZE + CELL_SIZE;
	SDL_RenderCopyEx(_Renderer, _Tcorner, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);

	angle = 90.0f;
	_rect.x = _width * CELL_SIZE + CELL_SIZE;
	_rect.y = 0;
	SDL_RenderCopyEx(_Renderer, _Tcorner, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);

	angle = 270.0f;
	_rect.x = 0;
	_rect.y =  _height * CELL_SIZE + CELL_SIZE;
	SDL_RenderCopyEx(_Renderer, _Tcorner, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);
}

void SdlGraphics::drawWalls(void) {
	float angle = 180.0f;

	for (int y = 1; y <= _height; y++)
	{
		_rect.x = 0;
		_rect.y =  y * CELL_SIZE;
		SDL_RenderCopyEx(_Renderer, _Twall, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);
	}
	angle = 270.0f;
	for (int x = 1; x <= _width; x++)
	{
		_rect.x = x * CELL_SIZE;
		_rect.y =  0;
		SDL_RenderCopyEx(_Renderer, _Twall, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);
	}
	angle = 90.0f;
	for (int x = 1; x <= _width; x++)
	{
		_rect.x = x * CELL_SIZE;
		_rect.y =  _height * CELL_SIZE + CELL_SIZE;
		SDL_RenderCopyEx(_Renderer, _Twall, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);
	}
	angle = 0.0f;
	for (int y = 1; y <= _width; y++)
	{
		_rect.x = _width * CELL_SIZE + CELL_SIZE;
		_rect.y =   y * CELL_SIZE;
		SDL_RenderCopyEx(_Renderer, _Twall, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);
	}
}

void			SdlGraphics::drawMap( void )
{
	drawCorners();
	drawWalls();
}

void			SdlGraphics::drawSnake( std::list<std::pair<int, int> > & snake, int direction) {
	(void)snake;
	(void)direction;
}

void			SdlGraphics::drawEntities( std::list<AEntities *> & entitiesList )
{
	SDL_Texture *	_Tentitie;

	for (std::list<AEntities *>::const_iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		_rect.x = (*it)->coordX() * CELL_SIZE + CELL_SIZE;
		_rect.y = (*it)->coordY() * CELL_SIZE + CELL_SIZE;
		if ((*it)->getName() == "Apple")
			_Tentitie = _Tapple;
		else
			_Tentitie = _Tegg;
		SDL_RenderCopyEx(_Renderer, _Tentitie, &_crop , &_rect, 0.0f, &_center, SDL_FLIP_NONE);
	}
}
void			SdlGraphics::drawScore( int score )
{
	SDL_Color		couleurBlanc;
	SDL_Rect		rect;
	SDL_Surface		*texte = NULL;
	const char			*c_text;

	couleurBlanc.r = 255;
	couleurBlanc.g = 255;
	couleurBlanc.b = 255;

	c_text = ("Score " + std::to_string(score)).c_str();

	rect.x = 10;
	rect.y =  _height * CELL_SIZE + CELL_SIZE * 2;
	rect.h = 28;
	rect.w = _width * strlen(c_text);

	texte = TTF_RenderText_Solid(_police, c_text, couleurBlanc);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(_Renderer, texte);
	SDL_RenderCopy(_Renderer, Message, NULL, &rect);
}

void			SdlGraphics::drawTime( int min, int sec ) {(void)min;(void)sec;}
void			SdlGraphics::drawGameOver(  )
{
	SDL_Color		couleurBlanc;
	SDL_Rect		rect;
	SDL_Surface		*texte = NULL;

	couleurBlanc.r = 255;
	couleurBlanc.g = 255;
	couleurBlanc.b = 255;

	rect.x = (_width * CELL_SIZE)/2 - (CELL_SIZE)*2;
	rect.y = (_height * CELL_SIZE)/2 + (CELL_SIZE)/2;
	rect.h = 28;
	rect.w = _width * 20;

	texte = TTF_RenderText_Solid(_police, "Game Over", couleurBlanc);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(_Renderer, texte);
	SDL_RenderCopy(_Renderer, Message, NULL, &rect);

	rect.x = (_width * CELL_SIZE)/2 - (CELL_SIZE)*2;
	rect.y = (_height * CELL_SIZE)/2 + (CELL_SIZE)/2 + 32;
	rect.h = 28;
	rect.w = _width * 20;

	texte = TTF_RenderText_Solid(_police, "Press Enter", couleurBlanc);
	Message = SDL_CreateTextureFromSurface(_Renderer, texte);
	SDL_RenderCopy(_Renderer, Message, NULL, &rect);
}

void			SdlGraphics::drawAll( std::list<std::pair<int, int> > & snake, int direction, std::list<AEntities *> & entitiesList, int score, bool gameover, int min, int sec)
{
	(void)snake;
	(void)direction;
	(void)entitiesList;
	(void)score;
	(void)gameover;
	(void)min;
	(void)sec;
	SDL_RenderClear(_Renderer);
	drawMap();
	drawEntities(entitiesList);
	drawScore( score );
	if (gameover)
		drawGameOver();
	SDL_RenderPresent(_Renderer);
}
