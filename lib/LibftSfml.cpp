#include <iostream>
#include "LibftSfml.hpp"

SfmlGraphics::SfmlGraphics():
_name("Tralalala")
{}

SfmlGraphics::SfmlGraphics( SfmlGraphics const & rhs )
{
	*this = rhs;
}

SfmlGraphics::~SfmlGraphics()
{}

SfmlGraphics &		SfmlGraphics::operator=( SfmlGraphics const & rhs )
{
	_name = rhs.getName();
	return *this;
}

std::string		SfmlGraphics::getName( void ) const { return _name; }

void			SfmlGraphics::introduce( void ) const
{
	std::cout << _name << std::endl;
}

SfmlGraphics		*createGraphic( void )
{
	return new SfmlGraphics();
}

void			deleteGraphic( SfmlGraphics *graphic )
{
	delete graphic;
}
