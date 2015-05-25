#ifndef SNAKE_HPP
# define SNAKE_HPP

class Snake
{
public:
	Snake(  );
	Snake( Snake const & _ );
	virtual ~Snake(  );

	Snake &	operator=( Snake const & _ );

	void				update( float dt );
	void				add_node();

private:
	std::map<int, int>	_nodes;
	float				_speed;
	int					_direction;
	int					_last_direction;
};

#endif
