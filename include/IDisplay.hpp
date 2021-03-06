#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

class IDisplayLib
{
	virtual t_input		getInput(  ) = 0;
	virtual void		drawMap(  ) = 0;
	virtual void		drawSnake( std::list<std::pair<int, int>> const & snake ) = 0;
	virtual void		drawEntities( std::list<std::pair<int, int>> const & entities ) = 0;
	virtual void		drawGameOver(  ) = 0;
	virtual void		drawInfo(  ) = 0;
};

#endif
