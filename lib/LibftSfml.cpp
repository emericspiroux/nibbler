#include <iostream>
#include "LibftSfml.hpp"

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
	_window.create(sf::VideoMode(x * CELL_SIZE, y * CELL_SIZE), "Nibbler");
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
		}
	}
	return (0);
}

void			SfmlGraphics::drawMap( void ) {}

void			SfmlGraphics::drawSnake( std::list<std::pair<int, int> > & snake ) {
	sf::Texture texture;
	sf::Image image;
	sf::Sprite sprite;
	std::list<std::pair<int, int> >::iterator it_tail;

	it_tail = snake.end();
	it_tail--;
	for (std::list<std::pair<int, int> >::iterator it = snake.begin(); it != snake.end(); ++it)
	{
		if (it == snake.begin())
		{
			if (image.loadFromFile("sprites/head-snake.png"))
			{
				image.createMaskFromColor(sf::Color::White);
				texture.loadFromImage(image, sf::IntRect(0, 0, 32, 32));
				sprite.setTexture(texture);
				sprite.setPosition(it->first * CELL_SIZE, it->second * CELL_SIZE);
			}
		}
		else if (it == it_tail)
		{
			if (image.loadFromFile("sprites/tail-snake.png"))
			{
				image.createMaskFromColor(sf::Color::White);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				sprite.setPosition(it->first * CELL_SIZE, it->second * CELL_SIZE);
			}
		}
		else
		{
			if (image.loadFromFile("sprites/body-snake.png"))
			{
				image.createMaskFromColor(sf::Color::White);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				sprite.setPosition(it->first * CELL_SIZE, it->second * CELL_SIZE);
			}
		}
		_window.draw(sprite);
	}
}

void			SfmlGraphics::drawEntities( std::list<AEntities *> & entitiesList )
{
	sf::Texture texture;
	sf::Image image;
	sf::Sprite sprite;

	for (std::list<AEntities *>::const_iterator it = entitiesList.begin(); it != entitiesList.end(); ++it)
	{
		if (image.loadFromFile("sprites/apple.png"))
		{
			image.createMaskFromColor(sf::Color::White);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			sprite.setPosition((*it)->coordX() * CELL_SIZE, (*it)->coordY() * CELL_SIZE);
			_window.draw(sprite);
		}
	}
}
void			SfmlGraphics::drawScore( int score ) {(void)score;}
void			SfmlGraphics::drawTime( int min, int sec ) {(void)min;(void)sec;}
void			SfmlGraphics::drawGameOver(  ) {}

void			SfmlGraphics::drawAll( std::list<std::pair<int, int> > & snake, std::list<AEntities *> & entitiesList, int score, bool gameover, int min, int sec)
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
	drawSnake(snake);
	drawEntities(entitiesList);
	_window.display();
}
