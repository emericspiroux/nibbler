#include <iostream>
#include "lib.hpp"

Graphics::Graphics():
_name("Tralalala")
{}

Graphics::Graphics( Graphics const & rhs )
{
	*this = rhs;
}

Graphics::~Graphics()
{}

Graphics &		Graphics::operator=( Graphics const & rhs )
{
	_name = rhs.getName();
	return *this;
}

std::string		Graphics::getName( void ) const { return _name; }

void			Graphics::introduce( void ) const
{
	std::cout << _name << std::endl;
}

Graphics		*createGraphic( void )
{
	return new Graphics();
}

void			deleteGraphic( Graphics *graphic )
{
	delete graphic;
}
