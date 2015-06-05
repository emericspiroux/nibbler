#ifndef AENTITIES_CLASS_HPP
# define AENTITIES_CLASS_HPP

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

	virtual void		update( time_t dt );

private:
	int		_x;
	int		_y;
	float	_duration;
	int		_score;
	bool	_collidable;
};

#include "MapTools.class.hpp"

#endif
