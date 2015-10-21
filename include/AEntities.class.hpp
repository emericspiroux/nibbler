#ifndef AENTITIES_CLASS_HPP
# define AENTITIES_CLASS_HPP

# include <iostream>
# include <stdlib.h>
# include <time.h>
# include <list>

class AEntities
{
public:
	AEntities ( );
	AEntities( int height, int width, std::list<AEntities *> list_ent, std::list< std::pair<int, int> > snake_nodes);
	AEntities( AEntities const & rhs );
	virtual ~AEntities(  );

	AEntities & operator=( AEntities const & _ );

	/* GETTERS & SETTERS */
	void				setX(int x);
	void				setY(int y);
	void				setDuration(float duration);
	void				setScore(int score);
	void				setCollidable(bool collidable);

	int					getX() const;
	int					getY() const;
	float				getDuration() const;
	int					getScore() const;
	bool				getCollidable() const;

	virtual bool		update( time_t dt );
	virtual int			coordX( void );
	virtual int			coordY( void );
	virtual std::string	getName( void );

protected:
	int		_x;
	int		_y;
	float	_duration;
	time_t	_born;
	int		_score;
	bool	_collidable;

	bool				already_test(int x, int y, std::list<std::pair<int, int> > list_test);
};

#include "MapTools.class.hpp"

#endif
