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
    atexit( SDL_Quit );
    _window = SDL_CreateWindow(
        "Nibbler",                  // window title
        0,           // initial x position
        0,           // initial y position
        x * CELL_SIZE,                               // width, in pixels
        y * CELL_SIZE,                               // height, in pixels
        SDL_WINDOW_ALLOW_HIGHDPI                  // flags - see below
    );

    if ( _window == NULL)
    {
        std::cout << "Can't set video mode: "<< SDL_GetError( ) << std::endl;
        exit(-1);
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

void			SdlGraphics::drawMap( void )
{
/*	t_sprite	corner_left;
	t_sprite	left;
	t_sprite	corner_right;

	if (corner_left.image.loadFromFile("sprites/wall-corner-left.png"))
	{
		corner_left.texture.loadFromImage(corner_left.image, sf::IntRect(0, 0, 32, 32));
		corner_left.sprite.setTexture(corner_left.texture);
		corner_left.sprite.setPosition(0, 0);
		_window.draw(corner_left.sprite);
		corner_left.sprite.setRotation(180);
		corner_left.sprite.setPosition(_width * CELL_SIZE + CELL_SIZE*2, _height * CELL_SIZE + CELL_SIZE*2);
		_window.draw(corner_left.sprite);
	}
	if (left.image.loadFromFile("sprites/wall-left.png"))
	{
		left.texture.loadFromImage(left.image, sf::IntRect(0, 0, 32, 32));
		left.sprite.setTexture(left.texture);
		for (int y = 1; y <= _height; y++)
		{
			left.sprite.setPosition(0, y * CELL_SIZE);
			_window.draw(left.sprite);
		}
		left.sprite.setRotation(90);
		for (int x = 1; x <= _width; x++)
		{
			left.sprite.setPosition(x * CELL_SIZE + CELL_SIZE, 0);
			_window.draw(left.sprite);
		}
		left.sprite.setRotation(270);
		for (int x = 1; x <= _width; x++)
		{
			left.sprite.setPosition(x * CELL_SIZE, _height * CELL_SIZE + CELL_SIZE*2);
			_window.draw(left.sprite);
		}
		left.sprite.setRotation(180);
		for (int y = 1; y <= _height; y++)
		{
			left.sprite.setPosition(_width * CELL_SIZE + CELL_SIZE*2, y * CELL_SIZE + CELL_SIZE);
			_window.draw(left.sprite);
		}
	}
	if (corner_right.image.loadFromFile("sprites/wall-corner-right.png"))
	{
		corner_right.image.createMaskFromColor(sf::Color::White);
		corner_right.texture.loadFromImage(corner_right.image, sf::IntRect(0, 0, 32, 32));
		corner_right.sprite.setTexture(corner_right.texture);
		corner_right.sprite.setPosition(_width * CELL_SIZE + CELL_SIZE, 0);
		_window.draw(corner_right.sprite);
		corner_right.sprite.setRotation(180);
		corner_right.sprite.setPosition(32, _height * CELL_SIZE + CELL_SIZE * 2);
		_window.draw(corner_right.sprite);
	}*/
}

void			SdlGraphics::drawSnake( std::list<std::pair<int, int> > & snake, int direction) {
	(void)snake;
	(void)direction;
}

void			SdlGraphics::drawEntities( std::list<AEntities *> & entitiesList )
{
	(void) entitiesList;
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
}
