/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 16:11:43 by larry             #+#    #+#             */
/*   Updated: 2015/10/11 13:49:09 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.class.hpp"
#include "IDisplayLib.hpp"

	Game::Game()
	{

	}

	Game::~Game()
	{
	}

	Game::Game( int width, int height )
	{
		this->_shouldClose = false;
		this->setWidth(width);
		this->setHeight(height);
		handle = dlopen("lib/libftcurse.dylib", RTLD_NOW);
		if (!handle)
		{
			std::cout << "Error opening dynlib" << std::endl;
			exit (1);
		}
		this->GraphicCreator = (IDisplayLib *(*)(int, int)) dlsym(handle, "createGraphic");
		if (!GraphicCreator)
		{
			std::cout << "Error finding symbol creator" << std::endl;
			exit (1);
		}
		this->GraphicDestructor = (void (*)(IDisplayLib *)) dlsym(handle, "deleteGraphic");
		if (!GraphicDestructor)
		{
			std::cout << "Error finding symbol destructor" << std::endl;
			exit (1);
		}
		this->_gobj = GraphicCreator(width, height);
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
		return (*this);
	}

	void					Game::setWidth( int width) {this->_width = width;}
	void					Game::setHeight( int height) {this->_height = height;}
	void					Game::setScore( int score){this->_score = score;};
	void					Game::setSnake( Snake * snake) {this->_snake = snake;}
	void					Game::setEntities( std::list<AEntities *> entities) {this->_entities = entities;}
	void					Game::setGameOver( bool gameover) {this->_gameOver = gameover;}
	void					Game::setShouldClose( bool shouldclose) {this->_shouldClose = shouldclose;}

	int						Game::getWidth( void ) const {return (this->_width);}
	int						Game::getHeight( void ) const {return (this->_height);}
	int						Game::getScore(void) const {return (this->_score);};
	Snake *					Game::getSnake( void ) const {return (this->_snake);}
	std::list<AEntities *>	Game::getEntities( void ) const {return (this->_entities);}
	bool					Game::getGameOver( void ) const {return (this->_gameOver);}
	bool					Game::getShouldClose( void ) const {return (this->_shouldClose);}

	/* Flush the entities map and create a new level */
	void					Game::createLevel(std::string filename)
	{
		(void)filename;
	}


	/* launch the main game loop */
	void					Game::start(  )
	{
		//typedef std::chrono::high_resolution_clock 		clock_;
		std::chrono::high_resolution_clock::time_point  before, now;
		std::chrono::duration<double> 					time_span;
		std::chrono::milliseconds					    dt;
		time_t											dtc;
		int												wait_time;

		time(&dtc);
		Snake *snake = new Snake( this->getHeight(), this->getWidth(), 4);
		this->setSnake(snake);
		Apple *apple = new Apple( this->getHeight(), this->getWidth(), this->getEntities(), snake->getNodes());
		this->addEntities(apple);
		this->_snake->setSpeed(0.25);
		while (!this->end())
		{
			before = std::chrono::high_resolution_clock::now();
			this->update(dtc);
			this->render();
			now = std::chrono::high_resolution_clock::now();
			time_span = std::chrono::duration_cast<std::chrono::duration<double> >(now - before);
			wait_time = (1000000 * this->_snake->getSpeed()) - (time_span.count() * 1000000);
			usleep(wait_time);
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
		return (this->_shouldClose);
	}


	/* call display getInput and process it ( stop || snake direction || switchDylib ) */
	void					Game::getInput(  )
	{
		this->_snake->setDirection(_gobj->getInput());
	}

	void					Game::switchDylib(  )
	{

	}

	/* call snake and entities update */
	void					Game::update(time_t dt)
	{
		std::list<AEntities *>::iterator it_en;
		AEntities *object;

		this->getInput();
		if ((object = this->_snake->update(dt, &this->_gameOver, &this->_entities)) != nullptr)
		{
			this->setScore(object->getScore());
			this->delEntities(object);
			Apple *apple = new Apple(this->getHeight(), this->getWidth(), this->getEntities(), this->getSnake()->getNodes());
			this->addEntities(apple);
		}

		for (it_en=this->_entities.begin(); it_en!=this->_entities.end(); ++it_en)
			(*it_en)->update(dt);
	}

	/* render map / entities / snake / game over */
	void					Game::render(  )
	{
		std::list<std::pair<int, int> > cpy_snake;

		cpy_snake = this->_snake->getNodes();
		this->_gobj->drawAll(cpy_snake, this->_entities);
	}


	/* render test map / entities / snake / game over  for testing game*/
	void					Game::renderTest(  )
	{
		int											i = 1;
		std::list<std::pair<int, int> >::iterator	it_sn;
		std::list<std::pair<int, int> >				snake_node;
		Snake 										*snake;

		//system("clear");
		std::cout<<"Map size: "<< this->getHeight()  << "/" << this->getWidth() << std::endl;

		snake = this->_snake;
		snake_node = snake->getNodes();
		for (it_sn=snake_node.begin(); it_sn!=snake_node.end(); ++it_sn)
		{
			std::cout<<"Snake Coord "<< i <<": ("<< it_sn->first  << "," << it_sn->second << ")" << std::endl;
			i++;
		}
	}

	/* add Entities to the game */
	void					Game::addEntities(AEntities *elem)
	{
		std::list<AEntities *> *list;

		list = &this->_entities;
		list->insert(list->begin(), elem);
	}

	/* add Entities to the game */
	void					Game::delEntities(AEntities *elem)
	{
		std::list<AEntities *> *list;

		list = &this->_entities;
		list->remove(elem);
	}
