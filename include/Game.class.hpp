#ifndef GAME_HPP
# define GAME_HPP

# include <list>
# include "nibbler.hpp"

class Game
{
public:
	Game(  );
	Game( int width, int height );
	Game( Game const & _ );
	virtual ~Game(  );

	Game &	operator=( Game const & _ );

	int						getWidth(  ) const;
	int						getHeight(  ) const;
	Snake *					getSnake(  ) const;
	std::list<Entities *>	getEntities(  ) const;
	
	/* add an item to the entities map */
	void					createItem(  );
	/* Flush the entities map and create a new level */
	void					createLevel( /* std::string ou std::list<Entities *> */ );

	/* launch the main game loop */
	void					start(  );
	/* set the _shouldClose bool to true */
	void					stop(  );
	/* get _shouldClose */
	bool					end(  );

	/* call display getInput and process it ( stop || snake direction || switchDylib ) */
	void					getInput(  );
	void					switchDylib(  );
	/* call sanke and entities update */
	void					update(  );
	/* render map / entities / snake / game over */
	void					render(  );

private:
	int						_width;
	int						_height;
	Snake *					_snake;
	std::list<Entities *>	_entities;
	bool					_gameOver;
	bool					_shouldClose;
}

#endif
