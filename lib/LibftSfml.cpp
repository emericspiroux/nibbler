#include <iostream>
#include "LibftSfml.hpp"

SfmlGraphics::SfmlGraphics():
_name("SFML Graphics")
{
	std::cout << "SFML Graphic CREATION" << std::endl;
}

SfmlGraphics::SfmlGraphics( SfmlGraphics const & rhs )
{
	*this = rhs;
}

SfmlGraphics::~SfmlGraphics()
{
	std::cout << "SFML Graphic DESTRUCTION" << std::endl;
}

SfmlGraphics		*createGraphic( void )
{
	return new SfmlGraphics();
}

void			deleteGraphic( SfmlGraphics *graphic )
{
	delete graphic;
}

SfmlGraphics &		SfmlGraphics::operator=( SfmlGraphics const & rhs )
{
	_name = rhs.getName();
	return *this;
}

std::string		SfmlGraphics::getName( void ) const { return _name; }

void			SfmlGraphics::clearScreen( void ) {}

void			SfmlGraphics::init( void ) const
{
	std::cout << _name << std::endl;
}

void			SfmlGraphics::drawMap( void ) {}

void			SfmlGraphics::drawAll( void ) {}
