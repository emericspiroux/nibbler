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
    //atexit( SDL_Quit );
    _window = SDL_CreateWindow(
        "Nibbler",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        x * CELL_SIZE + CELL_SIZE * 2,                               // width, in pixels
        y * CELL_SIZE + CELL_SIZE * 2,                               // height, in pixels
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
}

SdlGraphics::SdlGraphics( SdlGraphics const & rhs )
{
	*this = rhs;
}

SdlGraphics::~SdlGraphics()
{
	std::cout << "Sdl Graphic DESTRUCTION" << std::endl;
	SDL_DestroyWindow(_window);
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
					case SDLK_BACKSPACE:
						return (K_CT);
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
	float angle = 0.0f;
	for (std::list<AEntities *>::const_iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		_rect.x = (*it)->coordX() * CELL_SIZE + CELL_SIZE;
		_rect.y = (*it)->coordY() * CELL_SIZE + CELL_SIZE;
		SDL_RenderCopyEx(_Renderer, _Tapple, &_crop , &_rect, angle, &_center, SDL_FLIP_NONE);
	}
}
void			SdlGraphics::drawScore( int score ) {(void)score;}
void			SdlGraphics::drawTime( int min, int sec ) {(void)min;(void)sec;}
void			SdlGraphics::drawGameOver(  ) {}

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
	SDL_RenderPresent(_Renderer);
}
