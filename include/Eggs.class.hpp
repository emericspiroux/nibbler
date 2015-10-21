/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Eggs.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 14:58:53 by larry             #+#    #+#             */
/*   Updated: 2015/10/21 14:53:36 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EGGS_CLASS_HPP
# define EGGS_CLASS_HPP

# include "AEntities.class.hpp"

# define EGGS_SCORE 100
# include <list>
# include <map>

class Eggs : public AEntities
{
	public:
		Eggs();
		Eggs( int height, int width, std::list<AEntities *> list_ent, std::list<std::pair<int, int> > snake_nodes );
		virtual 			~Eggs(  );
		virtual void		update( time_t dt );
		virtual int			coordX( void );
		virtual int			coordY( void );
		virtual std::string	getName( void );
};

#endif
