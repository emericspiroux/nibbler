#ifndef LIBFTSdl_HPP
# define LIBFTSdl_HPP

# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <stdlib.h>
# include <stdio.h>
# include "IDisplayLib.hpp"

# define CELL_SIZE 32

class SdlGraphics: public IDisplayLib
{
public:
	SdlGraphics(  );
	SdlGraphics( int x, int y );
	SdlGraphics( SdlGraphics const & _ );
	virtual ~SdlGraphics(  );

	SdlGraphics &	operator=( SdlGraphics const & _ );

	void			clearScreen();
	void			init( void ) const;
	void			drawMap( void );
	void			drawSnake( std::list<std::pair<int, int> > & snake, int direction);
	void			drawEntities( std::list<AEntities *> & entitiesList );
	void			drawScore( int score );
	void			drawGameOver(  );
	void			drawTime( int min, int sec );
	void			drawAll( std::list<std::pair<int, int> > & snake, int direction, std::list<AEntities *> & entitiesList, int score, bool gameover, int min, int sec);

	int				getInput( void );

	std::string		getName( void ) const;

private:
	std::string		_name;
	int				_width;
	int				_height;
	SDL_Window *	_window;
	SDL_Renderer *	_Renderer;
	SDL_Texture *	_Tcorner;
	SDL_Texture *	_Twall;
	SDL_Texture *	_Tapple;
	SDL_Rect		_rect;
	SDL_Rect		_crop;
	SDL_Point		_center;
	TTF_Font *		_police;


	void			drawCorners(void);
	void			drawWalls(void);
};

extern "C" {

	SdlGraphics	*createGraphic( int x, int y );

	void			deleteGraphic( SdlGraphics *graphics );

}

#endif
