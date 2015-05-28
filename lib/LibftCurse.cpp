#include <iostream>
#include <ncurses.h>
#include "LibftCurse.hpp"

CurseGraphics::CurseGraphics():
_name("Curse Display")
{
	std::cout << "CURSE Graphic CREATION" << std::endl;
	initscr();
}

CurseGraphics::CurseGraphics( CurseGraphics const & rhs )
{
	*this = rhs;
}

CurseGraphics::~CurseGraphics()
{
	endwin();
	std::cout << "CURSE Graphic DESTRUCTION" << std::endl;
}

CurseGraphics &	CurseGraphics::operator=( CurseGraphics const & rhs )
{
	_name = rhs.getName();
	return *this;
}

std::string		CurseGraphics::getName( void ) const { return _name; }

void			CurseGraphics::introduce( void ) const
{
	printw(_name.c_str());
	refresh();
	getch();
}

CurseGraphics	*createGraphic( void )
{
	return new CurseGraphics();
}

void			deleteGraphic( CurseGraphics *graphic )
{
	delete graphic;
}
