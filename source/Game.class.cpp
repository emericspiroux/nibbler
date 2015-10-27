/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.class.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 16:11:43 by larry             #+#    #+#             */
/*   Updated: 2015/10/23 22:00:12 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.class.hpp"
#include "IDisplayLib.hpp"

#include <string.h>
#include <errno.h>

	Game::Game()
	{

	}

	Game::~Game()
	{
	}

	Game::Game( int width, int height )
	{
		this->_shouldClose = false;
		this->_gameOver = false;
		this->setWidth(width);
		this->setHeight(height);
		this->setContinue(true);
		this->setGameOver(false);
		this->setScore(0);
		this->setTime(0);
		this->setPause(false);
		handle = dlopen("lib/libftsfml.dylib", RTLD_LAZY | RTLD_LOCAL);
		if (!handle)
		{
			std::cerr << dlerror() << std::endl;
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
		this->_continue = rhs.getContinue();
		this->_shouldClose = rhs.getShouldClose();
		return (*this);
	}

	void					Game::setWidth( int width) {this->_width = width;}
	void					Game::setHeight( int height) {this->_height = height;}
	void					Game::setScore( int score){this->_score = score;};
	void					Game::addScore( int score){this->_score += score;};
	void					Game::setSnake( Snake * snake) {this->_snake = snake;}
	void					Game::setEntities( std::list<AEntities *> entities) {this->_entities = entities;}
	void					Game::setGameOver( bool gameover) {this->_gameOver = gameover;}
	void					Game::setContinue( bool again ) {this->_continue = again;}
	void					Game::setPause( bool pause ) {this->_pause = pause;}
	void					Game::setTime( int z_time ) {this->_time = z_time;}
	void					Game::setShouldClose( bool shouldclose) {this->_shouldClose = shouldclose;}

	int						Game::getWidth( void ) const {return (this->_width);}
	int						Game::getHeight( void ) const {return (this->_height);}
	int						Game::getScore(void) const {return (this->_score);};
	Snake *					Game::getSnake( void ) const {return (this->_snake);}
	std::list<AEntities *>	Game::getEntities( void ) const {return (this->_entities);}
	bool					Game::getGameOver( void ) const {return (this->_gameOver);}
	bool					Game::getContinue( void ) const {return (this->_continue);}
	bool					Game::getPause( void ) const {return (this->_pause);}
	int						Game::getTime( void ) const {return (this->_time);}
	bool					Game::getShouldClose( void ) const {return (this->_shouldClose);}

	/* Flush the entities map and create a new level */
	void					Game::createLevel(std::string filename)
	{
		(void)filename;
	}


	/* launch the main game loop */
	bool					Game::start(  )
	{
		//typedef std::chrono::high_resolution_clock 		clock_;
		std::chrono::high_resolution_clock::time_point  before, now;
		std::chrono::duration<double> 					time_span;
		std::chrono::milliseconds					    dt;
		int												wait_time;

		do
		{
			Snake *snake = new Snake( this->getHeight(), this->getWidth(), 4);
			this->setSnake(snake);
			Apple *apple = new Apple( this->getHeight(), this->getWidth(), this->getEntities(), snake->getNodes());
			this->addEntities(apple);
			this->_snake->setSpeed(0.9);
			this->_snake->setDirection(2);
			this->_snake->setLastDirection(2);
			this->setGameOver(false);
			while (this->again())
			{
				before = std::chrono::high_resolution_clock::now();
				if (!this->getInput())
					break ;
				if (!this->getPause())
					this->update(_time);
				this->render();
				now = std::chrono::high_resolution_clock::now();
				time_span = std::chrono::duration_cast<std::chrono::duration<double> >(now - before);
				wait_time = (250000 * this->_snake->getSpeed()) - (time_span.count() * 10000);
				if (wait_time >= 0)
					usleep(wait_time);

			}
			this->reset();
		}while (!this->end());
		GraphicDestructor(_gobj);
		return (true);
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

	bool					Game::again(  )
	{
		return (this->_continue);
	}

	void					Game::pause(  )
	{
		if (this->_pause == false)
			this->_pause = true;
		else
			this->_pause = false;
	}

	void					Game::reset(  )
	{
		this->clearEntities();
		this->setContinue(true);
		this->setTime(0);
		this->setScore(0);
		delete this->_snake;
	}


	/* call display getInput and process it ( stop || snake direction || switchDylib ) */
	bool					Game::getInput(  )
	{
		int					current_keycode;

		if ((current_keycode = _gobj->getInput()))
		{
			if (current_keycode == K_EX)
			{
				this->stop();
				return (false);
			}
			else if (current_keycode == K_PA)
				this->pause();
			else if (current_keycode == K_CT)
				this->setContinue(false);
			else if (current_keycode == K_L1 || current_keycode == K_L2 || current_keycode == K_L3)
				this->switchDylib(current_keycode);
			else if (!_gameOver && !_pause)
				this->_snake->setDirection(current_keycode);
		}
		return (true);
	}

	void					Game::switchDylib( int lib_key )
	{
		std::string			lib_path;

		this->setPause(true);
		GraphicDestructor(_gobj);
		dlclose(handle);
		if (lib_key == K_L1)
			lib_path = "lib/libftcurse.dylib";
		else if (lib_key == K_L2)
			lib_path = "lib/libftsfml.dylib";
		else if (lib_key == K_L3)
			lib_path = "lib/libftsdl.dylib";
		handle = dlopen(lib_path.c_str(), RTLD_LAZY | RTLD_LOCAL);
		if (!handle)
		{
			std::cerr << dlerror() << std::endl;
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
		this->_gobj = GraphicCreator(_width, _height);
	}

	/* call snake and entities update */
	void					Game::update(time_t dt)
	{
		std::list<AEntities *>::iterator it_en;
		AEntities *object;

		if (this->_gameOver == false)
		{
			for (it_en=this->_entities.begin(); it_en!=this->_entities.end(); ++it_en)
			{
				if ((*it_en)->update(dt))
				{
					this->delEntities((*it_en));
				}
			}
			if ((object = this->_snake->update(dt, &this->_gameOver, &this->_entities)) != nullptr)
			{
				this->addScore(object->getScore());
				if (object->getName() == "Apple")
				{
					// this->takeChance();
					if (this->_snake->getSpeed() > 0.3)
						this->_snake->setSpeed(this->_snake->getSpeed() - 0.02);
					Apple *apple = new Apple(this->getHeight(), this->getWidth(), this->getEntities(), this->getSnake()->getNodes());
					this->addEntities(apple);
				}
				this->delEntities(object);
			}
		}
	}


	/* render map / entities / snake / game over */
	void					Game::render(  )
	{
		std::list<std::pair<int, int> >		cpy_snake;
		std::time_t							min_dt = 0;
		std::time_t							sec_dt = 0;

		cpy_snake = this->_snake->getNodes();
		sec_dt = getDt();
		if ((min_dt = sec_dt / 60) != 0)
			sec_dt %= 60;
		this->_gobj->drawAll(cpy_snake, this->_snake->getDirection(), _entities, _score, _gameOver, _pause, min_dt, sec_dt);
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

	void					Game::clearEntities(void)
	{
		_entities.clear();
	}

	/* add Special Entities randomly */
	void					Game::takeChance(void)
	{
		int chance;

		chance = (rand() % 100);
		if (chance <= 10)
		{
			Eggs *eggs = new Eggs( this->getHeight(), this->getWidth(), this->getEntities(), _snake->getNodes());
			this->addEntities(eggs);
		} else if (chance <= 20)
		{
			Wall *wall = new Wall( this->getHeight(), this->getWidth(), this->getEntities(), _snake->getNodes());
			this->addEntities(wall);
		}
	}

	std::time_t				Game::getDt(void)
	{
		static std::time_t					sec_dt = 0;
		static std::time_t					new_result = 0;
		static std::time_t					pause_time = 0;

		if (_time == 0)
			_time = std::time(nullptr);
		if (!_gameOver)
			new_result = std::time(nullptr);

		if (_pause && pause_time == 0)
			pause_time = std::time(nullptr);
		else if (!_pause && pause_time != 0)
		{
			_time += new_result - pause_time;
			pause_time = 0;
		}

		if (!_pause)
			sec_dt = new_result - _time;

		return (sec_dt);
	}
