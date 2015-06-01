#ifndef LIBFTCURSE_HPP
# define LIBFTCURSE_HPP

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
	void			drawAll( void );

	std::string		getName( void ) const;
	int				getWidth( void ) const;
	int				getHeight( void ) const;

private:
	std::string		_name;
	int				_width;
	int				_height;
};

extern "C" {

	CurseGraphics	*createGraphic( int w, int h );

	void			deleteGraphic( CurseGraphics *graphics );

}

#endif
