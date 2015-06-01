#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include <list>
# include <utility>

class IDisplayLib
{
public:
	virtual void		clearScreen( void ) = 0;
	virtual void		drawMap( void ) = 0;
	virtual void		drawAll( void ) = 0;
	virtual void		drawSnake( std::list<std::pair<int, int> > & snake ) = 0;
/*
	virtual int			getInput(  ) = 0;
	virtual void		drawEntities( std::map<int, int> const & entities ) = 0;
	virtual void		drawGameOver(  ) = 0;
	virtual void		drawInfo(  ) = 0;
*/
	virtual void		init( void ) const = 0;
};

#endif
