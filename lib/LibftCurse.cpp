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

void			CurseGraphics::drawSnake( std::list<std::pair<int, int> > & snake, int direction )
{
	(void)direction;
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

void			CurseGraphics::drawScore( int score )
{
	std::string		sent;

	sent = "Score " + std::to_string(score);
	mvwprintw(_window, _height + 1, 1, sent.c_str());
}

void			CurseGraphics::drawGameOver(  )
{
	mvwprintw(_window, _height/2, _width - 3, "Game Over");
	mvwprintw(_window, _height/2 + 1, _width - 4, "Press Enter");

}

void			CurseGraphics::drawTime( int min, int sec )
{
	std::string		sent;
	std::string		str_min;
	std::string		str_sec;


	str_min = ((min >= 10)?"":"0") + std::to_string(min);
	str_sec = ((sec >= 10)?"":"0") + std::to_string(sec);
	mvwprintw(_window, 0, _width - 4, ("Time " + str_min + ":" + str_sec).c_str());
}

void			CurseGraphics::drawAll( std::list<std::pair<int, int> > & snake, int direction, std::list<AEntities *> & entitiesList, int score, bool gameover, int min, int sec)
{
	this->clearScreen();
	this->drawMap();
	this->drawEntities(entitiesList);
	this->drawSnake(snake, direction);
	this->drawScore(score);
	this->drawTime(min, sec);
	if (gameover)
		this->drawGameOver();
	wrefresh(_window);
}

int				CurseGraphics::getInput( void )
{
	int			key[3];

	nodelay(_window, TRUE);
	noecho();
	for (int i = 0; i < 3; i++)
		key[i] = wgetch(_window);
	return (key_compare(key[0], key[1], key[2]));
}

int				CurseGraphics::key_compare(int a, int b, int c)
{
	if ( a == 27 && b == 91 && c == 65)
		return (K_UP);
	if ( a == 27 && b == 91 && c == 67)
		return (K_LT);
	if ( a == 27 && b == 91 && c == 66)
		return (K_DW);
	if ( a == 27 && b == 91 && c == 68)
		return (K_RT);
	if ( a == 27 && b == -1 && c == -1)
		return (K_EX);
	if ( a == 10 && b == -1 && c == -1)
		return (K_CT);
	else return (0);
}
