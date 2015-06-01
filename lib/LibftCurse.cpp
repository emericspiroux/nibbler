#include <iostream>
#include <ncurses.h>
#include "LibftCurse.hpp"

CurseGraphics::CurseGraphics():
_name("Curse Display")
{
	std::cout << "CURSE Graphic CREATION" << std::endl;
	initscr();
}

CurseGraphics::CurseGraphics( int w, int h ):
_name("Curse Display"), _width(w), _height(h)
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

CurseGraphics	*createGraphic( int w, int h )
{
	return new CurseGraphics(w, h);
}

void			deleteGraphic( CurseGraphics *graphic )
{
	delete graphic;
}

CurseGraphics &	CurseGraphics::operator=( CurseGraphics const & rhs )
{
	_name = rhs.getName();
	return *this;
}

std::string		CurseGraphics::getName( void ) const { return _name; }
int				CurseGraphics::getWidth( void ) const { return _width; }
int				CurseGraphics::getHeight( void ) const { return _height; }

void			CurseGraphics::clearScreen( void )
{
	clear();
}

void			CurseGraphics::init( void ) const
{
	printw(_name.c_str());
	refresh();
	getch();
}

void			CurseGraphics::drawMap( void )
{
	border('|', '|', '-', '-', '+', '+', '+', '+');
}

void			CurseGraphics::drawAll( void )
{
	refresh();
}
