#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include <list>
# include <utility>
# include "AEntities.class.hpp"

class IDisplayLib
{
public:
	virtual void		clearScreen( void ) = 0;
	virtual void		drawMap( void ) = 0;
	virtual void		drawSnake( std::list<std::pair<int, int> > & snake, int direction ) = 0;
	virtual void		drawAll( std::list<std::pair<int, int> > & snake, int direction, std::list<AEntities *> & entitiesList,  int score, bool gameover, int min, int sec) = 0;

	virtual int			getInput( void ) = 0;
	virtual void		drawEntities( std::list<AEntities *> & entitiesList ) = 0;
	virtual void		drawScore( int score ) = 0;
	virtual void		drawTime( int min, int sec ) = 0;
	virtual void		drawGameOver(  ) = 0;
	/*virtual void		drawInfo(  ) = 0;
*/
	virtual void		init( void ) const = 0;
};

#endif
