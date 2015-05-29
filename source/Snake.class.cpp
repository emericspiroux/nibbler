# include "Snake.class.hpp"

Snake::Snake(  ){}

Snake::Snake( game _game, unsigned int lenght)
{
	this->setGame(_game);
	//create snake with lenght
}

Snake::Snake( Snake const & rhs )
{
	*this = rhs;
}

Snake &	Snake::operator=( Snake const & rhs )
{
	this->_nodes = rhs.getNodes();
	this->_speed = rhs.getSpeed();
	this->_direction = rhs.getDirection();
	this->_last_direction = rhs.getLastDirection();
	this->_game = rhs.getGame();
	return (*this);
}

/* Getters & Setters */
void					Snake::setNodes(std::map<int, int> nodes) { this->_nodes = nodes}
void					Snake::setSpeed(float speed) { this->_speed = speed}
void					Snake::setDirection( int direction ) { this->_direction = direction}
void					Snake::setLastDirection(int last_direction) { this->_last_direction = last_direction}
void					Snake::setGame(Game c_game) { this->_game = game}

std::map<int, int>		Snake::getNodes() const { return (this->_nodes); }
float					Snake::getSpeed() const { return (this->_speed); }
int						Snake::getDirection() const { return (this->_direction); }
int						Snake::getLastDirection() const { return (this->_last_direction); }
Game					Snake::getGame() const { return (this->_game);}


///////////////////////////////////////////////Regarder si en dehors de la map
void				Snake::update( time_t dt )
{
	std::map<int, int>:iterator  it_el;
	AEntities					 object;
	bool						 head;
	int							 dir;
	int							 x_head;
	int							 y_head;
	int							 x_save;
	int							 y_save;

	head = true;
	if (this->_game->getGameOver())	//&& dt > DT_MACRO ?
	{
		//Mettre tout les noeuds a la place du suivant
		for (it_el=this->_entities.begin(); it_el!=this->_entities.end(); ++it_el)
		{
			if (head)//avancer la tete
			{
				if (this->getLastDirection() != (dir = this->getDirection()))
				{
					x_save = it_el->first;
					y_save = it_el->second;
					switch (dir)
					{
						case 1:	x_head = it_el->first;
								y_head = it_el->second - 1:
								break;

						case 2:	x_head = it_el->first;
								y_head = it_el->second - 1:
								break;

						case 3:	x_head = it_el->first;
								y_head = it_el->second - 1:
								break;

						case 4:	x_head = it_el->first;
								y_head = it_el->second - 1:
								break;
					}
					if (this->eat_collidable(x_head, y_head))
						this->_game->setGameOver(true);
					else
					{
						it_el->first = x_head;
						it_el->second = y_head;
					}
					this->setLastDirection(dir);
				}
				head = false;
			}
			else // et le corps
			{
				it_el->first = x_save;
				it_el->second = y_save;
				x_save = it_el->first;
				y_save = it_el->second;
			}
		}
		if ((object = this->eat_good(x_head, y_head)) != nullptr)
		{
			this->_game->setScore(object->getScore());
			this->add_node(x_save, y_save);
		}
	}
}

void				Snake::add_node(int x, int y)
{
	std::map<int, int>	snake_node;
	snake_node = this->_node;
	snake_node.insert(snake_node.end(), std::pair<int,int>( x, y ));
}

bool				Snake::eat_collidable(int x, int y)
{
	Snake *							snake;
	std::list<AEntities *>			listEnti;
	std::list<AEntities *>:iterator	it_ent;
	std::map<int, int>:iterator		it_sn;

	listEnti = this->_game->getEntities();
	snake = this->_game->getSnake();

	//search in entities
	for (it_ent=this->_entities.begin(); it_ent!=this->_entities.end(); ++it_ent)
	{
		if (it_ent->getCollidable() == true && it_ent->getX() == x && it_ent->->getY() == y)
			return (true);
	}

	//search in snake
	for (it_sn=this->_entities.begin() + 1; it_sn!=this->_entities.end(); ++it_sn)
	{
		if (it_sn->first == x && it_sn->second == y)
			return (true);
	}
	return (false);
}

AEntities*				Snake::eat_good(int x, int y)
{
	std::list<AEntities *>				listEnti;
	std::list<AEntities *>:iterator		it_ent;

	listEnti = this->_game->getEntities();
	snake = this->_game->getSnake();

	//search in entities
	for (it_ent=this->_entities.begin(); it_ent!=this->_entities.end(); ++it_ent)
	{
		if (it_ent->getCollidable() == false && it_ent->getX() == x && it_ent->->getY() == y)
			return (it_ent);
	}
	return (nullptr);
}

