/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Eggs.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 15:04:06 by larry             #+#    #+#             */
/*   Updated: 2015/10/21 20:06:51 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Eggs.class.hpp"
#include <iostream>

Eggs::~Eggs()
{

}

Eggs::Eggs( int height, int width, std::list<AEntities *> list_ent, std::list<std::pair<int, int> > snake_nodes )
{
	int		rnd_x;
	int		rnd_y;
	bool	set;
	std::list<std::pair<int, int> > al_test;

	this->setDuration(3);
	this->setScore(EGGS_SCORE);
	this->setCollidable(false);
	_born = std::time(nullptr);

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


Eggs::Eggs( )
{
	this->setDuration(3);
	this->setScore(EGGS_SCORE);
	this->setCollidable(false);
	_born = std::time(nullptr);
}

Eggs::Eggs( int x, int y )
{
	this->setDuration(3);
	this->setScore(EGGS_SCORE);
	this->setCollidable(false);
	_born = std::time(nullptr);
	this->setX(x);
	this->setY(y);
}

bool		Eggs::update( time_t dt )
{
	std::time_t							sec_dt = 0;
	std::time_t							min_dt = 0;

	dt = std::time(nullptr);
	sec_dt = dt - _born;
	if ((min_dt = sec_dt / 60) != 0)
		sec_dt %= 60;

	if (sec_dt > this->_duration)
		return (true);
	return (false);
}

int			Eggs::coordX( void )
{
	return (this->_x);
}

int			Eggs::coordY( void )
{
	return (this->_y);
}

std::string	Eggs::getName( void )
{
	return ("Egg");
}
