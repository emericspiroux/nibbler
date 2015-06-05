/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTools.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/31 12:30:35 by larry             #+#    #+#             */
/*   Updated: 2015/06/02 18:41:32 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPTOOLS_CLASS_HPP
# define MAPTOOLS_CLASS_HPP

# include "AEntities.class.hpp"
# include "Snake.class.hpp"

class MapTools
{
public:
	MapTools(  );
	MapTools( MapTools const & _ );
	virtual ~MapTools(  );

	MapTools & operator=( MapTools const & rhs );

	/* Compare to the map and return if found */
	static bool				cmpMap(std::list<AEntities *> list_ent, std::list<std::pair<int, int> > map_sna, int x, int y);
	static bool				cmpSnake(std::list<std::pair<int, int> > map_sna, int x, int y);
	static bool				cmpAEntities(std::list<AEntities *> list_ent, int x, int y);

};

#endif
