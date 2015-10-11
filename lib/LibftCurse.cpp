#include <iostream>
#include "AEntities.class.hpp"
#include "LibftCurse.hpp"

CurseGraphics::CurseGraphics():
_name("Curse Display")
{
	std::cout << "CURSE Graphic CREATION" << std::endl;
	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_WHITE);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	_window = newwin(10, 10, 0, 0);
}

CurseGraphics::CurseGraphics( int w, int h ):
_name("Curse Display"), _width(w), _height(h)
{
	std::cout << "CURSE Graphic CREATION" << std::endl;
	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	init_pair(2, COLOR_WHITE, COLOR_WHITE);
	init_pair(3, COLOR_WHITE, COLOR_RED);
	_window = newwin(_height + 2, _width * 2 + 2, 0, 0);
}

CurseGraphics::CurseGraphics( CurseGraphics const & rhs )
{
	*this = rhs;
}

CurseGraphics::~CurseGraphics()
{
	delwin(_window);
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
	_width = rhs.getWidth();
	_height = rhs.getHeight();
	_window = rhs.getWindow();
	return *this;
}

std::string		CurseGraphics::getName( void ) const { return _name; }
int				CurseGraphics::getWidth( void ) const { return _width; }
int				CurseGraphics::getHeight( void ) const { return _height; }
WINDOW *		CurseGraphics::getWindow( void ) const { return _window; }

void			CurseGraphics::clearScreen( void )
{
	wclear(_window);
}

void			CurseGraphics::init( void ) const
{
	wprintw(_window, _name.c_str());
	wrefresh(_window);
}

void			CurseGraphics::drawMap( void )
{
	wborder(_window, '|', '|', '-', '-', '+', '+', '+', '+');
}

void			CurseGraphics::drawSnake( std::list<std::pair<int, int> > & snake )
{
	for (std::list<std::pair<int, int> >::iterator it = snake.begin(); it != snake.end(); ++it)
	{
		if (it == snake.begin())
			wattron(_window, COLOR_PAIR(1));
		else
			wattron(_window, COLOR_PAIR(2));
		mvwprintw(_window, it->second + 1,  it->first * 2 + 1, "  ");
		if (it == snake.begin())
			wattroff(_window, COLOR_PAIR(1));
		else
			wattroff(_window, COLOR_PAIR(2));
	}
}

void			CurseGraphics::drawEntities( std::list<AEntities *> & entitiesList )
{
	for (std::list<AEntities *>::const_iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		wattron(_window, COLOR_PAIR(3));
		mvwprintw(_window, (*it)->coordY() + 1, (*it)->coordX() * 2 + 1, "  ");
		wattroff(_window, COLOR_PAIR(3));
	}
}

void			CurseGraphics::drawAll( std::list<std::pair<int, int> > & snake, std::list<AEntities *> & entitiesList)
{
	this->clearScreen();
	this->drawMap();
	this->drawEntities(entitiesList);
	this->drawSnake(snake);
	wrefresh(_window);
}

int				CurseGraphics::getInput( void )
{
	int			keyboard;

	nodelay(_window, TRUE);
	noecho();
	cbreak();
	for (int i = 0; i < 3; i++)
		keyboard = wgetch(_window);
	switch (keyboard)
	{
		case 65:return (1);
				break ;
		case 67:return (2);
				break ;
		case 66:return (3);
				break ;
		case 68:return (4);
				break ;
	}
	return (0);
}
