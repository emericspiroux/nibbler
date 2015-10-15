/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 15:57:43 by larry             #+#    #+#             */
/*   Updated: 2015/10/15 14:30:04 by larry            ###   ########.fr       */
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
	this->setDirection(2);
	for (unsigned int i = 0; i <= lenght; i++)
		this->add_node((Widthmap/2) - i, (Heightmap/2));

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
	int								x_head;
	int								y_head;
	int								x_save;
	int								y_save;
	int								x_save_body;
	int								y_save_body;
	tnode							node;

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
				this->change_dir(&x_head, &y_head, it_el);
				node = this->fixedOutOfMap(x_head, y_head);
				if (this->eat_collidable(node.x, node.y, listEnt))
				{
					*game_over = true;
					return (nullptr);
				}
				it_el->first = node.x;
				it_el->second = node.y;
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
		if ((object = this->eat_good(node.x, node.y, listEnt)) != nullptr)
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

	//search in snake without head
	it_sn = this->_nodes.begin();
	it_sn++;
	for ((void)it_sn; it_sn!=this->_nodes.end(); ++it_sn)
	{
		if (it_sn->first == x && it_sn->second == y)
		{
			return (true);
		}
	}
	return (false);
}

AEntities*				Snake::eat_good(int x, int y, std::list<AEntities *> *listEnti)
{
	std::list<AEntities *>::iterator		it_ent;

	//search in entities
	for (it_ent=listEnti->begin(); it_ent!=listEnti->end(); ++it_ent)
	{
		if ((*it_ent)->getCollidable() == false && (*it_ent)->coordX() == x && (*it_ent)->coordY() == y)
		{
			std::cout << "Score :" << (*it_ent)->getScore() << std::endl;
			return (*it_ent);
		}
	}
	return (nullptr);
}

void					Snake::change_dir(int *x, int *y, std::list<std::pair<int, int> >::iterator it_el)
{
	int					x_save;
	int					y_save;
	bool				err;

	x_save = it_el->first;
	y_save = it_el->second;
	err = false;

	if (this->getDirection() == 0 && this->getLastDirection() == 0)
		this->setLastDirection(2);
	else if (this->getDirection() == 0)
		this->setDirection(this->getLastDirection());

	switch (this->getDirection())
	{
		case K_UP:	if (this->getLastDirection() != K_DW) y_save--; else err = true;
				break;

		case K_LT:	if (this->getLastDirection() != K_RT) x_save++; else err = true;
				break;

		case K_DW:	if (this->getLastDirection() != K_UP) y_save++; else err = true;
				break;

		case K_RT:	if (this->getLastDirection() != K_LT) x_save--; else err = true;
				break;

	}
	if (this->getDirection() != 0 && err == false)
		this->setLastDirection(this->getDirection());

	if (err == true)
	{
		switch (this->getLastDirection())
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
	}
	*x = x_save;
	*y = y_save;

}

struct snode			Snake::fixedOutOfMap(int x_head, int y_head)
{
	tnode				node;

	if (x_head > (this->getWidthMap() - 1))
	{
		node.x = 0;
		node.y = y_head;
	}
	else if (y_head > (this->getHeightMap()) - 1)
	{
		node.x = x_head;
		node.y = 0;
	}
	else if (x_head < 0)
	{
		node.x = this->getWidthMap() - 1;
		node.y = y_head;
	}
	else if (y_head < 0)
	{
		node.x = x_head;
		node.y = this->getHeightMap() - 1;
	}
	else
	{
		node.x = x_head;
		node.y = y_head;
	}
	return (node);
}

