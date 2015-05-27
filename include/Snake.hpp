#ifndef SNAKE_HPP
# define SNAKE_HPP

# include "Game.class.hpp"

class Snake
{
public:
	Snake(  );
	Snake( game _game );
	Snake( Snake const & _ );
	virtual ~Snake(  );

	Snake &	operator=( Snake const & _ );

	/* Getters & Setters */
	void					setNodes(std::map<int, int> nodes);
	void					setSpeed(float speed);
	void					setDirection( int direction );
	void					setLastDirection(int last_direction);
	void					setGame(Game c_game);

	std::map<int, int>		getNodes() const;
	float					getSpeed() const;
	int						getDirection() const;
	int						getLastDirection() const;
	Game					getGame() const;

	void				update( float dt );
	void				add_node();

private:
	std::map<int, int>	_nodes;
	float				_speed;
	int					_direction;
	int					_last_direction;
	Game				_game;
};

#endif
