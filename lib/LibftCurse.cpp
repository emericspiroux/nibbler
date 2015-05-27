#include <iostream>
#include <ncurses.h>
#include "LibftCurse.hpp"

CurseGraphics::CurseGraphics():
_name("Trololo")
{
	std::cout << "CURSE Graphic CREATION" << std::endl;
	initscr();			/* Start curses mode 		  */
	printw("Hello World !!!");	/* Print Hello World		  */
	refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
}

CurseGraphics::CurseGraphics( CurseGraphics const & rhs )
{
	*this = rhs;
}

CurseGraphics::~CurseGraphics()
{
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
