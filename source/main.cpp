/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 13:20:50 by larry             #+#    #+#             */
/*   Updated: 2015/10/15 14:57:47 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "nibbler.hpp"
#include "Game.class.hpp"

int		main( int argc, char **argv )
{
	Getopt	verif(argc, argv);
	bool	end;

	end = false;
	verif.setLimit(3);
	verif.addRules( 1, "unsigned_int|max[10]|is_numeric|min_int[10]|max_int[50]");
	verif.addRules( 2, "unsigned_int|max[10]|is_numeric|min_int[10]|max_int[50]");
	if (!verif.check())
		verif.myUsage("nibbler_usage");
	while (!end)
	{
		Game *game = new Game(atoi(argv[1]), atoi(argv[2]));
		end = game->start();
		delete game;
	}
	return (0);
}
