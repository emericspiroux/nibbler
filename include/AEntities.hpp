#ifndef AENTITIES_HPP
# define AENTITIES_HPP

class AEntities
{
public:
	AEntities(  );
	AEntities(int x, int y, float duration, int score, bool collidable);
	AEntities( AEntities const & _ );
	virtual ~AEntities(  );

	AEntities & operator=( AEntities const & _ );

	/* GETTERS & SETTERS */
	void			setX(int x);
	void			setY(int y);
	void			setDuration(float duration);
	void			setScore(int score);
	void			setCollidable(bool collidable);

	int				getX() const;
	int				getY() const;
	float			getDuration() const;
	int				getScore() const;
	bool			getCollidable() const;

	virtual update( float dt ) = 0;

private:
	int		_x;
	int		_y;
	float	_duration;
	int		_score;
	bool	_collidable;
};

#endif
