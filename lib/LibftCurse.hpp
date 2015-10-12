#ifndef LIBFTCURSE_HPP
# define LIBFTCURSE_HPP

# include <ncurses.h>
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
	void			drawSnake( std::list<std::pair<int, int> > & snake );
	void			drawEntities( std::list<AEntities *> & entitiesList );
	void			drawScore( int score );
	void			drawAll( std::list<std::pair<int, int> > & snake, std::list<AEntities *> & entitiesList, int score);

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
};

extern "C" {

	CurseGraphics	*createGraphic( int w, int h );

	void			deleteGraphic( CurseGraphics *graphics );

}

#endif
