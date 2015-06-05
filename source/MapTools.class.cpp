/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTools.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 12:37:50 by larry             #+#    #+#             */
/*   Updated: 2015/06/02 17:48:14 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MapTools.class.hpp"

MapTools::MapTools( void )
{

}

MapTools::MapTools( MapTools const & rhs )
{
	(void) rhs;
}

MapTools::~MapTools( void )
{

}

MapTools & MapTools::operator=( MapTools const & rhs )
{
	(void) rhs;
	return (*this);
}

bool				MapTools::cmpMap(std::list<AEntities *> list_ent, std::list<std::pair<int, int> > map_sna, int x, int y)
{
		std::list<AEntities *>::iterator it;
		std::list<std::pair<int, int> >::iterator it_sn;

		for (it_sn=map_sna.begin(); it_sn!=map_sna.end(); ++it_sn)
		{
			if (it_sn->first == x && it_sn->second == y)
				return (true);
		}
		for (it=list_ent.begin(); it!=list_ent.end(); ++it)
		{
			if ((*it)->getX() == x && (*it)->getY() == y)
				return (true);
		}
		return (false);
}

bool				MapTools::cmpSnake(std::list<std::pair<int, int> > map_sna, int x, int y)
{
		std::list<std::pair<int, int> >::iterator it_sn;

		for (it_sn=map_sna.begin(); it_sn!=map_sna.end(); ++it_sn)
		{
			if (it_sn->first == x && it_sn->second == y)
				return (true);
		}
		return (false);
}

bool				MapTools::cmpAEntities(std::list<AEntities *> list_ent, int x, int y)
{
		std::list<AEntities *>::iterator it;

		for (it=list_ent.begin(); it!=list_ent.end(); ++it)
		{
			if ((*it)->getX() == x && (*it)->getY() == y)
				return (true);
		}
		return (false);
}

