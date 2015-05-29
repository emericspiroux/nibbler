/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 15:57:39 by larry             #+#    #+#             */
/*   Updated: 2015/05/29 04:47:59 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include <list>
# include <time.h>
# include "nibbler.hpp"

class Game
{
public:
	Game( int width, int height );
	Game( Game const & _ );
	virtual ~Game(  );

	Game &	operator=( Game const & _ );

	void					setWidth( int width);
	void					setHeight( int width);
	void					setScore( int score);
	void					setHeight( int height);
	void					setSnake( Snake * snake);
	void					setEntities( std::list<AEntities> entities);
	void					setGameOver( bool gameover);
	void					setShouldClose( bool shouldclose);

	int						getWidth(void) const;
	int						getHeight(void) const;
	int						getScore(void) const;
	int						getHeight(void) const;
	Snake *					getSnake(void) const;
	std::list<AEntities *>	getEntities(void) const;
	bool					getGameOver(void) const;
	bool					getShouldClose(void) const;

	/* add an item to the entities map */
	void					createItem(void);
	/* Flush the entities map and create a new level */
	void					createLevel( /* std::list<Entities *> */ );

	/* launch the main game loop */
	void					start( void );
	/* set the _shouldClose bool to true */
	void					stop( void );
	/* get _shouldClose */
	bool					end(  );

	/* call display getInput and process it ( stop || snake direction || switchDylib ) */
	void					getInput(  );
	void					switchDylib(  );
	/* call sanke and entities update */
	void					update( time_t dt );
	/* render map / entities / snake / game over */
	void					render(  );

	/* render test map / entities / snake / game over */
	void					renderTest(  );

	/* watch if exist */
	bool					mapCmpSnake(int x, int y);
	bool					mapCmpEnt(int x, int y);

	/* add Entities to the game */
	void					addEntities(AEntities *elem);
private:
	int						_width;
	int						_height;
	int						_score;
	Snake *					_snake;
	std::list<AEntities *>	_entities;
	bool					_gameOver;
	bool					_shouldClose;

	Game(  );
};

#endif
