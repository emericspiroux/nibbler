/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 16:11:43 by larry             #+#    #+#             */
/*   Updated: 2015/05/28 21:16:57 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	Game::Game( int width, int height );
	{
		this->_shouldClose = false;
		this->setWidth(width);
		this->setHeight(height);
	}

	Game::Game( Game const & rhs )
	{
		*this = rhs;
	}

	Game &	Game::operator=( Game const & rhs )
	{
		this->_width = rhs.getWidth();
		this->_height = rhs.getHeight();
		this->_snake = rhs.getSnake();
		this->_entities = rhs.getEntities();
		this->_gameOver = rhs.getGameOver();
		this->_shouldClose = rhs.getShouldClose();
	}

	void					Game::setWidth( int width) {this->_width = width;}
	void					Game::setHeight( int height) {this->_height = height;}
	void					Game::setScore( int score){this->_score = score;};
	void					Game::setSnake( Snake * snake) {this->_snake = snake;}
	void					Game::setEntities( std::list<AEntities> entities) {this->_entities = entities;}
	void					Game::setGameOver( bool gameover) {this->_gameOver = gameOver;}
	void					Game::setShouldClose( bool shouldclose) {this->_shouldClose = shouldClose;}

	int						Game::getWidth( void ) const {return (this->_width);}
	int						Game::getHeight( void ) const {return (this->_height);}
	int						Game::getScore(void) const {return (this->_score);};
	Snake *					Game::getSnake( void ) const {return (this->_snake);}
	std::list<AEntities *>	Game::getEntities( void ) const {return (this->_entities);}
	bool					Game::getGameOver( void ) const {return (this->_gameOver);}
	bool					Game::getShouldClose( void ) const {return (this->_shouldClose);}

	/* add an item to the entities map */
	void					Game::createItem(void)
	{

	}

	/* Flush the entities map and create a new level */
	void					Game::createLevel( /* std::string ou std::list<Entities *> */ )
	{

	}


	/* launch the main game loop */
	void					Game::start( void )
	{
		time_t before;
		time_t now;
		time_t dt;

		time(&before);
		while (!this->end)
		{
			time(&now);
			dt = difftime(now, before);
			this->update(dt);
			this->renderTest();
			time(&before);
		}
	}

	/* set the _shouldClose bool to true */
	void					Game::stop( void )
	{
		this->_shouldClose = true;
	}

	/* get _shouldClose */
	bool					Game::end(  )
	{
		return (this->_shouldClose());
	}


	/* call display getInput and process it ( stop || snake direction || switchDylib ) */
	void					Game::getInput(  )
	{

	}

	void					Game::switchDylib(  )
	{

	}

	/* call snake and entities update */
	void					Game::update(time_t dt)
	{
		std::map<AEntities *>::iterator it_en;

		this->_snake->update(dt);
		for (it_en=this->_entities.begin(); it_en!=this->_entities.end(); ++it_en)
			this->_entities->update(dt);
	}

	/* render map / entities / snake / game over */
	void					Game::render(  )
	{

	}


	/* render test map / entities / snake / game over */
	void					Game::renderTest(  )
	{

	}

	/* watch if exist */
	bool					Game::mapCmpSnake(int x, int y)
	{
		if (this->_snake->getX() == x && this->_snake->getY() == y)
			return (true);
		return (false);
	}

	bool					Game::mapCmpEnt(int x, int y)
	{
		std::list<AEntities *>:iterator it;

		for (it=this->_entities.begin(); it!=this->_entities.end(); ++it)
		{
			if (it->getX() == x && it->getY() == y)
				return (true);
		}
		return (false);
	}


