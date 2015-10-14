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


int				SfmlGraphics::getInput( void )
{
	return (0);
}


void			SfmlGraphics::drawMap( void ) {}
void			SfmlGraphics::drawSnake( std::list<std::pair<int, int> > & snake ) { static_cast<void>(snake); }
void			SfmlGraphics::drawAll( std::list<std::pair<int, int> > & snake, std::list<AEntities *> & entitiesList, int score, bool gameover, int min, int sec) {(void)snake;(void)entitiesList;(void)score;(void)gameover;(void)min;(void)sec;}
void			SfmlGraphics::drawEntities( std::list<AEntities *> & entitiesList ) {(void)entitiesList;}
void			SfmlGraphics::drawScore( int score ) {(void)score;}
void			SfmlGraphics::drawTime( int min, int sec ) {(void)min;(void)sec;}
void			SfmlGraphics::drawGameOver(  ) {}
