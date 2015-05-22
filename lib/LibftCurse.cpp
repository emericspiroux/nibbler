#include <iostream>
#include "LibftCurse.hpp"

CurseGraphics::CurseGraphics():
_name("Trololo")
{}

CurseGraphics::CurseGraphics( CurseGraphics const & rhs )
{
	*this = rhs;
}

CurseGraphics::~CurseGraphics()
{}

CurseGraphics &	CurseGraphics::operator=( CurseGraphics const & rhs )
{
	_name = rhs.getName();
	return *this;
}

std::string		CurseGraphics::getName( void ) const { return _name; }

void			CurseGraphics::introduce( void ) const
{
	std::cout << _name << std::endl;
}

CurseGraphics	*createGraphic( void )
{
	return new CurseGraphics();
}

void			deleteGraphic( CurseGraphics *graphic )
{
	delete graphic;
}
