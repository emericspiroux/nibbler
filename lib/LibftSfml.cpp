#include <iostream>
#include "LibftSfml.hpp"

#include <unistd.h>

SfmlGraphics::SfmlGraphics():
_name("SFML Graphics")
{
	std::cout << "SFML Graphic CREATION" << std::endl;
	_window.create(sf::VideoMode(10 * CELL_SIZE, 10 * CELL_SIZE), "Nibbler");
}

SfmlGraphics::SfmlGraphics(int x, int y):
_name("SFML Graphics")
{
	std::cout << "SFML Graphic CREATION" << std::endl;
	_width = x;
	_height = y;
	_window.create(sf::VideoMode(x * CELL_SIZE + CELL_SIZE * 2, y * CELL_SIZE + CELL_SIZE * 2), "Nibbler");

	_corner.image.loadFromFile("sprites/wall-corner.png");
	_corner.texture.loadFromImage(_corner.image, sf::IntRect(0, 0, 32, 32));

	_wall.image.loadFromFile("sprites/wall.png");
	_wall.texture.loadFromImage(_wall.image, sf::IntRect(0, 0, 32, 32));

	_snake_head.image.loadFromFile("sprites/head-snake.png");
	_snake_head.image.createMaskFromColor(sf::Color::White);
	_snake_head.texture.loadFromImage(_snake_head.image, sf::IntRect(0, 0, 32, 32));
	_snake_head.sprite.setTexture(_snake_head.texture);
	_snake_head.sprite.setOrigin(16, 16);

	_snake_tail.image.loadFromFile("sprites/tail-snake.png");
	_snake_tail.image.createMaskFromColor(sf::Color::White);
	_snake_tail.texture.loadFromImage(_snake_tail.image);
	_snake_tail.sprite.setTexture(_snake_tail.texture);
	_snake_tail.sprite.setOrigin(16, 16);

	_snake_body.image.loadFromFile("sprites/body-snake.png");
	_snake_body.image.createMaskFromColor(sf::Color::White);
	_snake_body.texture.loadFromImage(_snake_body.image);
	_snake_body.sprite.setTexture(_snake_body.texture);
	_snake_body.sprite.setOrigin(16, 16);

	_snake_curve.image.loadFromFile("sprites/side-snake.png");
	_snake_curve.image.createMaskFromColor(sf::Color::White);
	_snake_curve.texture.loadFromImage(_snake_curve.image);
	_snake_curve.sprite.setTexture(_snake_curve.texture);
	_snake_curve.sprite.setOrigin(16, 16);
}

SfmlGraphics::SfmlGraphics( SfmlGraphics const & rhs )
{
	*this = rhs;
}

SfmlGraphics::~SfmlGraphics()
{
	std::cout << "SFML Graphic DESTRUCTION" << std::endl;
	_window.close();
}

SfmlGraphics	*createGraphic( int w, int h )
{
	return new SfmlGraphics(w, h);
}

void			deleteGraphic( SfmlGraphics *graphic )
{
	delete graphic;
}

SfmlGraphics &	SfmlGraphics::operator=( SfmlGraphics const & rhs )
{
	_name = rhs.getName();
	return *this;
}

std::string		SfmlGraphics::getName( void ) const { return _name; }

void			SfmlGraphics::clearScreen( void ) {
	_window.clear(sf::Color::Red);
}

void			SfmlGraphics::init( void ) const
{
	std::cout << _name << std::endl;
}

int				SfmlGraphics::getInput( void )
{
	sf::Event	event;

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return (K_EX);
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				return (K_EX);
			else if (event.key.code == sf::Keyboard::Up)
				return (K_UP);
			else if (event.key.code == sf::Keyboard::Right)
				return (K_LT);
			else if (event.key.code == sf::Keyboard::Left)
				return (K_RT);
			else if (event.key.code == sf::Keyboard::Down)
				return (K_DW);
			else if (event.key.code == sf::Keyboard::Return)
				return (K_CT);
			else if (event.key.code == sf::Keyboard::Num1)
				return (K_L1);
			else if (event.key.code == sf::Keyboard::Num3)
				return (K_L3);
		}
	}
	return (0);
}

void SfmlGraphics::drawCorners(void) {
	sf::Sprite  corner;

	corner.setTexture(_corner.texture);
	corner.setPosition(0, 0);
	_window.draw(corner);
	corner.setRotation(180);
	corner.setPosition(_width * CELL_SIZE + CELL_SIZE*2, _height * CELL_SIZE + CELL_SIZE*2);
	_window.draw(corner);
	corner.setRotation(90);
	corner.setPosition(_width * CELL_SIZE + CELL_SIZE*2, 0);
	_window.draw(corner);
	corner.setRotation(270);
	corner.setPosition(0, _height * CELL_SIZE + CELL_SIZE * 2);
	_window.draw(corner);
}

void SfmlGraphics::drawWalls(void) {
	sf::Sprite	wall;

	wall.setTexture(_wall.texture);
	for (int y = 1; y <= _height; y++)
	{
		wall.setPosition(0, y * CELL_SIZE);
		_window.draw(wall);
	}
	wall.setRotation(90);
	for (int x = 1; x <= _width; x++)
	{
		wall.setPosition(x * CELL_SIZE + CELL_SIZE, 0);
		_window.draw(wall);
	}
	wall.setRotation(270);
	for (int x = 1; x <= _width; x++)
	{
		wall.setPosition(x * CELL_SIZE, _height * CELL_SIZE + CELL_SIZE*2);
		_window.draw(wall);
	}
	wall.setRotation(180);
	for (int y = 1; y <= _height; y++)
	{
		wall.setPosition(_width * CELL_SIZE + CELL_SIZE*2, y * CELL_SIZE + CELL_SIZE);
		_window.draw(wall);
	}
	wall.setRotation(180);
}

void			SfmlGraphics::drawMap( void )
{
	drawCorners();
	drawWalls();
}

void			SfmlGraphics::drawSnake( std::list<std::pair<int, int> > & snake, int direction ) {
	std::list<std::pair<int, int> >::iterator it_tail;
	int			angle;

	it_tail = snake.end();
	it_tail--;

	for (std::list<std::pair<int, int> >::iterator it = snake.begin(); it != snake.end(); ++it)
	{
		if (it == snake.begin())
		{
				if (direction == 1)
					angle = 0;
				else if (direction == 2)
					angle = 90;
				else if (direction == 3)
					angle = 180;
				else
					angle = 270;
				_snake_head.sprite.setRotation(angle);
				_snake_head.sprite.setPosition(it->first * CELL_SIZE + CELL_SIZE + 16, it->second * CELL_SIZE + CELL_SIZE + 16);
				_window.draw(_snake_head.sprite);
		}
		else if (it == it_tail)
		{
				std::list<std::pair<int, int> >::iterator	it_body;

				it_body = it_tail--;
				if (it_tail->first == it_body->first)
				{
					if (it_tail->second == it_body->second + 1)
						angle = 180;
					else
						angle = 0;
				}
				else
				{
					if (it_tail->first == it_body->first + 1)
						angle = 90;
					else
						angle = 270;
				}
				_snake_tail.sprite.setRotation(angle);
				_snake_tail.sprite.setPosition(it->first * CELL_SIZE + CELL_SIZE + 16, it->second * CELL_SIZE + CELL_SIZE + 16);
				_window.draw(_snake_tail.sprite);
		}
		else
		{
			std::list<std::pair<int, int> >::iterator	it_body_prev;
			std::list<std::pair<int, int> >::iterator	it_body_next;
			// int angle = 0;

			it_body_prev = --it;
			it++;
			it_body_next = ++it;
			it--;

			// std::cout << "NODE" << std::endl;
			// std::cout << it_body_next->first << " : " << it_body_next->second << std::endl;
			// std::cout << it->first << " : " << it->second << std::endl;
			// std::cout << it_body_prev->first << " : " << it_body_prev->second << std::endl;

			if (it->first == it_body_prev->first && it->first == it_body_next->first)
			{
				_snake_body.sprite.setRotation(0);
				_snake_body.sprite.setPosition(it->first * CELL_SIZE + CELL_SIZE * 3/2, it->second * CELL_SIZE + CELL_SIZE * 3/2);
				_window.draw(_snake_body.sprite);
			}
			else if (it->second == it_body_prev->second && it->second == it_body_next->second)
			{
				_snake_body.sprite.setRotation(90);
				_snake_body.sprite.setPosition(it->first * CELL_SIZE + CELL_SIZE * 3/2, it->second * CELL_SIZE + CELL_SIZE * 3/2);
				_window.draw(_snake_body.sprite);
			}
			else
			{
				if ((it->first == it_body_next->first + 1 && it->second == it_body_prev->second + 1) ||
					(it->first == it_body_prev->first + 1 && it->second == it_body_next->second + 1) ||
					(it->first == it_body_next->first + 1 && it->second == it_body_prev->second - _height + 1) ||
					(it->first == it_body_prev->first + 1 && it->second == it_body_next->second - _height + 1) ||
					(it->first == it_body_next->first - _width + 1 && it->second == it_body_prev->second + 1) ||
					(it->first == it_body_prev->first - _width + 1 && it->second == it_body_next->second + 1))
				{
					_snake_curve.sprite.setRotation(180);
					_snake_curve.sprite.setPosition(it->first * CELL_SIZE + CELL_SIZE * 3/2, it->second * CELL_SIZE + CELL_SIZE * 3/2);
					_window.draw(_snake_curve.sprite);
				}
				if ((it->first == it_body_next->first - 1 && it->second == it_body_prev->second - 1) ||
					(it->first == it_body_prev->first - 1 && it->second == it_body_next->second - 1) ||
					(it->first == it_body_next->first - 1 && it->second == it_body_prev->second + _height - 1) ||
					(it->first == it_body_prev->first - 1 && it->second == it_body_next->second + _height - 1) ||
					(it->first == it_body_next->first + _width - 1 && it->second == it_body_prev->second - 1) ||
					(it->first == it_body_prev->first + _width - 1 && it->second == it_body_next->second - 1))
				{
					_snake_curve.sprite.setRotation(0);
					_snake_curve.sprite.setPosition(it->first * CELL_SIZE + CELL_SIZE * 3/2, it->second * CELL_SIZE + CELL_SIZE * 3/2);
					_window.draw(_snake_curve.sprite);
				}
				if ((it->first == it_body_prev->first + 1 && it->second == it_body_next->second - 1) ||
					(it->first == it_body_next->first + 1 && it->second == it_body_prev->second - 1) ||
					(it->first == it_body_next->first + 1 && it->second == it_body_prev->second + _height - 1) ||
					(it->first == it_body_prev->first + 1 && it->second == it_body_next->second + _height - 1) ||
					(it->first == it_body_next->first - _width + 1 && it->second == it_body_prev->second - 1) ||
					(it->first == it_body_prev->first - _width + 1 && it->second == it_body_next->second - 1))
				{
					_snake_curve.sprite.setRotation(90);
					_snake_curve.sprite.setPosition(it->first * CELL_SIZE + CELL_SIZE * 3/2, it->second * CELL_SIZE + CELL_SIZE * 3/2);
					_window.draw(_snake_curve.sprite);
				}
				if ((it->first == it_body_prev->first - 1 && it->second == it_body_next->second + 1) ||
					(it->first == it_body_next->first - 1 && it->second == it_body_prev->second + 1) ||
					(it->first == it_body_next->first - 1 && it->second == it_body_prev->second - _height + 1) ||
					(it->first == it_body_prev->first - 1 && it->second == it_body_next->second - _height + 1) ||
					(it->first == it_body_next->first + _width - 1 && it->second == it_body_prev->second + 1) ||
					(it->first == it_body_prev->first + _width - 1 && it->second == it_body_next->second + 1))
				{
					_snake_curve.sprite.setRotation(270);
					_snake_curve.sprite.setPosition(it->first * CELL_SIZE + CELL_SIZE * 3/2, it->second * CELL_SIZE + CELL_SIZE * 3/2);
					_window.draw(_snake_curve.sprite);
				}
			}
		}
	}
}

void			SfmlGraphics::drawEntities( std::list<AEntities *> & entitiesList )
{
	sf::Texture texture;
	sf::Image image;
	sf::Sprite sprite;

	for (std::list<AEntities *>::const_iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		if ((*it)->getName() == "Egg")
		{
			if (image.loadFromFile("sprites/egg.png"))
			{
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				sprite.setPosition((*it)->coordX() * CELL_SIZE + CELL_SIZE, (*it)->coordY() * CELL_SIZE + CELL_SIZE);
				_window.draw(sprite);
			}
		} else if ((*it)->getName() == "Apple"){
			if (image.loadFromFile("sprites/apple.png"))
			{
				image.createMaskFromColor(sf::Color::White);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				sprite.setPosition((*it)->coordX() * CELL_SIZE + CELL_SIZE, (*it)->coordY() * CELL_SIZE + CELL_SIZE);
				_window.draw(sprite);
			}
		} else
		{
			if (image.loadFromFile("sprites/wall-entitie.png"))
			{
				image.createMaskFromColor(sf::Color::White);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				sprite.setPosition((*it)->coordX() * CELL_SIZE + CELL_SIZE, (*it)->coordY() * CELL_SIZE + CELL_SIZE);
				_window.draw(sprite);
			}
		}
	}
}
void			SfmlGraphics::drawScore( int score ) {(void)score;}
void			SfmlGraphics::drawTime( int min, int sec ) {(void)min;(void)sec;}
void			SfmlGraphics::drawGameOver(  ) {}

void			SfmlGraphics::drawAll( std::list<std::pair<int, int> > & snake, int direction, std::list<AEntities *> & entitiesList, int score, bool gameover, int min, int sec)
{
	sf::Texture texture;
	sf::Image image;
	sf::Sprite sprite;

	(void)snake;
	(void)entitiesList;
	(void)score;
	(void)gameover;
	(void)min;
	(void)sec;

	_window.clear();
	drawSnake(snake, direction);
	drawMap();
	drawEntities(entitiesList);
	_window.display();
}
