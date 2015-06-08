/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 15:57:43 by larry             #+#    #+#             */
/*   Updated: 2015/06/08 11:41:02 by jvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Snake.class.hpp"
# include <iostream>
Snake::Snake(  ){}

Snake::~Snake(  ){}

Snake::Snake( int Heightmap, int Widthmap, unsigned int lenght)
{
	this->setHeightMap(Heightmap);
	this->setWidthMap(Widthmap);
	for (unsigned int i = 0; i <= lenght; i++)
	{
		this->add_node((Widthmap/2) - i, (Heightmap/2));
		std::cout << "Add node :" << " (" << (Widthmap/2) - i << "," << (Heightmap/2) << ")" << std::endl;
	}
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
	return (*this);
}

/* Getters & Setters */
void					Snake::setNodes(std::list<std::pair<int, int> > nodes) { this->_nodes = nodes;}
void					Snake::setHeightMap(int Heightmap) { this->_heightMap = Heightmap;}
void					Snake::setWidthMap(int Widthmap) { this->_widthMap = Widthmap;}
void					Snake::setSpeed(float speed) { this->_speed = speed;}
void					Snake::setDirection( int direction ) { this->_direction = direction;}
void					Snake::setLastDirection(int last_direction) { this->_last_direction = last_direction;}

std::list<std::pair<int, int> >		Snake::getNodes() const { return (this->_nodes); }
int						Snake::getHeightMap() const { return (this->_heightMap); };
int						Snake::getWidthMap() const { return (this->_widthMap); };
float					Snake::getSpeed() const { return (this->_speed); }
int						Snake::getDirection() const { return (this->_direction); }
int						Snake::getLastDirection() const { return (this->_last_direction); }

AEntities *				Snake::update(time_t dt, bool *game_over, std::list<AEntities *> *listEnt)
{
	std::list<std::pair<int, int> >::iterator	it_el;
	AEntities						*object;
	bool							head;
	int								dir = 2;
	int								x_head;
	int								y_head;
	int								x_save;
	int								y_save;
	int								x_save_body;
	int								y_save_body;

	head = true;
	(void)dt;
	if (1)	//&& dt > DT_MACRO ?
	{
		//Mettre tout les noeuds a la place du suivant
		for (it_el=this->_nodes.begin(); it_el!=this->_nodes.end(); ++it_el)
		{
			if (!game_over)
				return (nullptr);
			if (head)//avancer la tete
			{
				x_save = it_el->first;
				y_save = it_el->second;
				this->change_dir(dir, &x_head, &y_head, it_el);
				if (this->eat_collidable(x_head, y_head, listEnt))
					*game_over = true;
				else if (x_head > this->getWidthMap())
				{
					it_el->first = 0;
					it_el->second = y_head;
				}
				else if (y_head > this->getHeightMap())
				{
					it_el->first = x_head;
					it_el->second = 0;
				}
				else if (x_head < 0)
				{
					it_el->first = this->getWidthMap();
					it_el->second = y_head;
				}
				else if (y_head < 0)
				{
					it_el->first = x_head;
					it_el->second = this->getHeightMap();
				}
				else
				{
					it_el->first = x_head;
					it_el->second = y_head;
				}
				head = false;
			}
			else // et le corps
			{
				x_save_body = it_el->first;
				y_save_body = it_el->second;
				it_el->first = x_save;
				it_el->second = y_save;
				x_save = x_save_body;
				y_save = y_save_body;
			}
		}
		if ((object = this->eat_good(x_head, y_head, listEnt)) != nullptr)
		{
			this->add_node(x_save, y_save);
			return (object);
		}
	}
	return (nullptr);
}

void				Snake::add_node(int x, int y)
{
	std::list<std::pair<int, int> >	*snake_node;

	snake_node = &this->_nodes;
	snake_node->insert(snake_node->end(), std::pair<int,int>( x, y ));
}

bool				Snake::eat_collidable(int x, int y, std::list<AEntities *> *listEnt)
{
	std::list<std::pair<int, int> >		*snake;
	std::list<AEntities *>::iterator	it_ent;
	std::list<std::pair<int, int> >::iterator		it_sn;

	snake = &this->_nodes;

	//search in entities
	for (it_ent=listEnt->begin(); it_ent!=listEnt->end(); ++it_ent)
	{
		if ((*it_ent)->getCollidable() == true && (*it_ent)->getX() == x && (*it_ent)->getY() == y)
			return (true);
	}

	//search in snake
	it_sn = this->_nodes.begin();
	it_sn++;
	for ((void)it_sn; it_sn!=this->_nodes.end(); ++it_sn)
	{
		if (it_sn->first == x && it_sn->second == y)
			return (true);
	}
	return (false);
}

AEntities*				Snake::eat_good(int x, int y, std::list<AEntities *> *listEnti)
{
	std::list<AEntities *>::iterator		it_ent;

	//search in entities
	for (it_ent=listEnti->begin(); it_ent!=listEnti->end(); ++it_ent)
	{
		if ((*it_ent)->getCollidable() == false && (*it_ent)->getX() == x && (*it_ent)->getY() == y)
			return (*it_ent);
	}
	return (nullptr);
}

void					Snake::change_dir(int dir, int *x, int *y, std::list<std::pair<int, int> >::iterator it_el)
{
	int					x_save;
	int					y_save;
	x_save = it_el->first;
	y_save = it_el->second;


	std::cout << "head : " << x_save << "/" << y_save << std::endl;
	switch (dir)
	{
		case 1:	y_save--;
				break;

		case 2:	x_save++;
				break;

		case 3:	y_save++;
				break;

		case 4:	x_save--;
				break;
	}
	*x = x_save;
	*y = y_save;
	this->setLastDirection(dir);
}

