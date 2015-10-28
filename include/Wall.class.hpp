/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 14:58:53 by larry             #+#    #+#             */
/*   Updated: 2015/10/22 16:26:34 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_CLASS_HPP
# define WALL_CLASS_HPP

# include "AEntities.class.hpp"

# include <list>
# include <map>

class Wall : public AEntities
{
	public:
		Wall();
		Wall( int height, int width, std::list<AEntities *> list_ent, std::list<std::pair<int, int> > snake_nodes );
		Wall(int x, int y);
		virtual 			~Wall(  );
		virtual bool		update( time_t dt );
		virtual int			coordX( void );
		virtual int			coordY( void );
		virtual std::string	getName( void );
};

#endif
