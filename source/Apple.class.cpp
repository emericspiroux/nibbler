/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Apple.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 15:04:06 by larry             #+#    #+#             */
/*   Updated: 2015/10/21 17:30:04 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Apple.class.hpp"
#include <iostream>

Apple::~Apple()
{

}

Apple::Apple( int height, int width, std::list<AEntities *> list_ent, std::list<std::pair<int, int> > snake_nodes )
{
	int		rnd_x;
	int		rnd_y;
	bool	set;
	std::list<std::pair<int, int> > al_test;

	//Too slow and freeze game with big snake
	this->setDuration(-1);
	this->setScore(APPLE_SCORE);
	this->setCollidable(false);

	set = false;
	srand (time(NULL));
	while (!set)
	{
		do
		{
			rnd_x = (rand() % width) + 0;
			rnd_y = (rand() %  height) + 0;
			if (!this->already_test(rnd_x, rnd_y, al_test))
			{
				al_test.insert(al_test.end(), std::pair<int,int>( rnd_x, rnd_y ));
				if (!MapTools::cmpMap(list_ent, snake_nodes, rnd_x, rnd_y))
				{
					this->setX(rnd_x);
					this->setY(rnd_y);
					set = true;
				}
				break ;
			}
		}while(1);
	}
}


Apple::Apple( )
{
	this->setDuration(-1);
	this->setScore(APPLE_SCORE);
	this->setCollidable(false);
}

bool		Apple::update( time_t dt )
{
	(void)dt;
	return (false);
}

int			Apple::coordX( void )
{
	return (this->_x);
}

int			Apple::coordY( void )
{
	return (this->_y);
}

std::string	Apple::getName( void )
{
	return ("Apple");
}
