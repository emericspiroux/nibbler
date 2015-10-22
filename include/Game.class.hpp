/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 15:57:39 by larry             #+#    #+#             */
/*   Updated: 2015/10/22 17:00:47 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_CLASS_HPP
# define GAME_CLASS_HPP

# include <list>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <thread>
# include <chrono>
# include <dlfcn.h>
# include "nibbler.hpp"
# include "AEntities.class.hpp"
# include "Snake.class.hpp"
# include "Eggs.class.hpp"
# include "Wall.class.hpp"
# include "Apple.class.hpp"
# include "Eggs.class.hpp"
# include "IDisplayLib.hpp"

class Game
{
public:
	Game(  );
	Game( int width, int height );
	Game( Game const & _ );
	virtual ~Game(  );

	Game &	operator=( Game const & _ );

	void					setWidth( int width);
	void					setHeight( int width);
	void					setScore( int score);
	void					addScore( int score);
	void					setSnake( Snake * snake);
	void					setEntities( std::list<AEntities *> entities);
	void					setGameOver( bool gameover);
	void					setContinue( bool again);
	void					setTime( int z_time );
	void					setShouldClose( bool shouldclose);

	int						getWidth(void) const;
	int						getHeight(void) const;
	int						getScore(void) const;
	Snake *					getSnake(void) const;
	std::list<AEntities *>	getEntities(void) const;
	bool					getGameOver(void) const;
	bool					getContinue(void) const;
	int						getTime(void) const;
	bool					getShouldClose(void) const;

	/* Flush the entities map and create a new level */
	void					createLevel( std::string filename);

	/* launch the main game loop */
	bool					start( void );
	/* set the _shouldClose bool to true */
	void					stop( void );
	/* set the _shouldClose bool to true */
	bool					again( void );
	/* get _shouldClose */
	bool					end(  );

	/* call display getInput and process it ( stop || snake direction || switchDylib ) */
	bool					getInput(  );
	void					switchDylib( int lib_key );
	/* call sanke and entities update */
	void					update( time_t dt );
	/* render map / entities / snake / game over */
	void					render(  );

	/* render test map / entities / snake / game over */
	void					renderTest(  );

	/* add Entities to the game */
	void					addEntities(AEntities *elem);

	/* del Entities*/
	void					delEntities(AEntities *elem);

	/*add special entities randomly*/
	void					takeChance(void);

private:
	int						_width;
	int						_height;
	int						_score;
	int						_time;
	Snake *					_snake;
	std::list<AEntities *>	_entities;
	bool					_gameOver;
	bool					_continue;
	bool					_shouldClose;
	void *					handle;
	IDisplayLib				*(*GraphicCreator)(int, int);
	void					(*GraphicDestructor)(IDisplayLib *);
	IDisplayLib *			_gobj;
};

#endif
