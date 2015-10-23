#ifndef LIBFTSFML_HPP
# define LIBFTSFML_HPP

# include <SFML/Graphics.hpp>
# include "IDisplayLib.hpp"

# define CELL_SIZE 32

typedef struct		s_sprite
{
		sf::Texture	texture;
		sf::Image	image;
		sf::Sprite	sprite;
}					t_sprite;

class SfmlGraphics: public IDisplayLib
{
public:
	typedef sf::RenderWindow	t_rw;
	SfmlGraphics(  );
	SfmlGraphics( int x, int y );
	SfmlGraphics( SfmlGraphics const & _ );
	virtual ~SfmlGraphics(  );

	SfmlGraphics &	operator=( SfmlGraphics const & _ );

	void			clearScreen();
	void			init( void ) const;
	void			drawMap( void );
	void			drawSnake( std::list<std::pair<int, int> > & snake, int direction );
	void			drawEntities( std::list<AEntities *> & entitiesList );
	void			drawScore( int score );
	void			drawGameOver(  );
	void			drawTime( int min, int sec );
	void			drawAll( std::list<std::pair<int, int> > & snake, int direction, std::list<AEntities *> & entitiesList, int score, bool gameover, int min, int sec);
	int				getInput( void );
	std::string		getName( void ) const;

private:
	std::string		_name;
	int				_width;
	int				_height;
	t_rw			_window;
	t_sprite		_corner;
	t_sprite		_wall;
	t_sprite		_snake_head;
	t_sprite		_snake_tail;
	t_sprite		_snake_body;
	t_sprite		_snake_curve;
	sf::Font		_MyFont;

	void			drawCorners(void);
	void			drawWalls(void);

};

extern "C" {

	SfmlGraphics	*createGraphic( int x, int y );

	void			deleteGraphic( SfmlGraphics *graphics );

}

#endif
