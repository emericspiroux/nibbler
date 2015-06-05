/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Apple.class.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 15:04:06 by larry             #+#    #+#             */
/*   Updated: 2015/06/03 14:40:08 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Apple.class.hpp"

Apple::~Apple()
{

}

Apple::Apple( int height, int width, std::list<AEntities *> list_ent, std::list<std::pair<int, int> > snake_nodes )
{
	int		rnd_x;
	int		rnd_y;
	bool	set;

	set = false;
	this->setDuration(-1);
	this->setScore(APPLE_SCORE);
	this->setCollidable(false);
	while (!set)
	{
		srand (time(NULL));
		rnd_x = rand() % width + 0;
		rnd_y = rand() %  height + 0;
		if (!MapTools::cmpMap(list_ent, snake_nodes, rnd_x, rnd_y))
		{
			this->setX(rnd_x);
			this->setY(rnd_y);
			set = true;
		}
	}
}


Apple::Apple( )
{
	this->setDuration(-1);
	this->setScore(APPLE_SCORE);
	this->setCollidable(false);
}

void	Apple::update( time_t dt )
{
	(void)dt;
}
