#ifndef LIBFTSFML_HPP
# define LIBFTSFML_HPP

# include "IDisplayLib.hpp"

class SfmlGraphics: public IDisplayLib
{
public:
	SfmlGraphics(  );
	SfmlGraphics( SfmlGraphics const & _ );
	virtual ~SfmlGraphics(  );

	SfmlGraphics &	operator=( SfmlGraphics const & _ );

	void			clearScreen();
	void			init( void ) const;
	void			drawMap( void );
	void			drawAll( void );

	std::string		getName( void ) const;

private:
	std::string		_name;
};

extern "C" {

	SfmlGraphics	*createGraphic( void );

	void			deleteGraphic( SfmlGraphics *graphics );

}

#endif
