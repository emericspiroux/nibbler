#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include <map>

class IDisplayLib
{
public:
/*
	virtual int			getInput(  ) = 0;
	virtual void		drawMap(  ) = 0;
	virtual void		drawSnake( std::map<int, int> const & snake ) = 0;
	virtual void		drawEntities( std::map<int, int> const & entities ) = 0;
	virtual void		drawGameOver(  ) = 0;
	virtual void		drawInfo(  ) = 0;
*/
	virtual void		introduce( void ) const = 0;
};

#endif
