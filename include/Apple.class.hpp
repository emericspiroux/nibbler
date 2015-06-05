/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Apple.class.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/29 14:58:53 by larry             #+#    #+#             */
/*   Updated: 2015/06/03 14:40:12 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLE_CLASS_HPP
# define APPLE_CLASS_HPP

# include "AEntities.class.hpp"

# define APPLE_SCORE 10
# include <list>
# include <map>

class Apple : public AEntities
{
	public:
		Apple();
		Apple( int height, int width, std::list<AEntities *> list_ent, std::list<std::pair<int, int> > snake_nodes );
		virtual 			~Apple(  );
		virtual void		update( time_t dt );
};

#endif
