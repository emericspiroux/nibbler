#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <string>
# include <vector>
# include "AEntities.class.hpp"

class Snake
{
public:
	Snake(  );
	Snake( int height, int width, unsigned int lenght);
	Snake( Snake const & _ );
	virtual ~Snake(  );

	Snake &	operator=( Snake const & _ );

	/* Getters & Setters */
	void					setNodes(std::list<std::pair<int, int> > nodes);
	void					setSpeed(float speed);
	void					setDirection( int direction );
	void					setLastDirection(int last_direction);
	void					setHeightMap(int Heightmap);
	void					setWidthMap(int Widthmap);

	std::list<std::pair<int, int> >		getNodes() const;
	float					getSpeed() const;
	int						getDirection() const;
	int						getLastDirection() const;
	int						getHeightMap() const;
	int						getWidthMap() const;

	AEntities *				update(time_t dt, bool *game_over, std::list<AEntities *> *listEnt);
	void					add_node(int x, int y);
	bool					eat_collidable(int x, int y, std::list<AEntities *> *listEnt);
	AEntities*				eat_good(int x, int y, std::list<AEntities *> *listEnt);

private:
	std::list<std::pair<int, int> >	_nodes;
	float				_speed;
	int					_direction;
	int					_heightMap;
	int					_widthMap;
	int					_last_direction;

protected:
	void					change_dir(int *x, int *y, std::list<std::pair<int, int> >::iterator it_el);
};

#endif
