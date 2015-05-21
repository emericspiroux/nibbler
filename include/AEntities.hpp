#ifndef AENTITIES_HPP
# define AENTITIES_HPP

class AEntities
{
public:
	/* GETTERS & SETTERS TROOLOLOL */
	/* COPLIEN HERE */

	virtual update( float dt ) = 0;

private:
	int		_x;
	int		_y;
	float	_duration;
	int		_score;
	bool	_collidable;
}

#endif
