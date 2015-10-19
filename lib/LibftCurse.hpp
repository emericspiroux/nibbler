#ifndef LIBFTCURSE_HPP
# define LIBFTCURSE_HPP

# include <ncurses.h>
# include <time.h>
# include "IDisplayLib.hpp"

class CurseGraphics: public IDisplayLib
{
public:
	CurseGraphics(  );
	CurseGraphics( int w, int h );
	CurseGraphics( CurseGraphics const & _ );
	virtual ~CurseGraphics(  );

	CurseGraphics &	operator=( CurseGraphics const & _ );

	void			clearScreen();
	void			init( void ) const;
	void			drawMap( void );
	void			drawSnake( std::list<std::pair<int, int> > & snake, int direction );
	void			drawEntities( std::list<AEntities *> & entitiesList );
	void			drawScore( int score );
	void			drawGameOver(  );
	void			drawTime( int min, int sec );
	void			drawAll( std::list<std::pair<int, int> > & snake, int direction, std::list<AEntities *> & entitiesList, int score, bool gameover, int min, int sec);

	int				getInput( void );

	std::string		getName( void ) const;
	int				getWidth( void ) const;
	int				getHeight( void ) const;
	WINDOW *		getWindow( void ) const;

private:
	std::string		_name;
	int				_width;
	int				_height;
	WINDOW *		_window;

	int 			key_compare(int a, int b, int c);
};

extern "C" {

	CurseGraphics	*createGraphic( int w, int h );

	void			deleteGraphic( CurseGraphics *graphics );

}

#endif
