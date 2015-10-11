/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntities.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 16:55:27 by larry             #+#    #+#             */
/*   Updated: 2015/10/11 15:38:11 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "AEntities.class.hpp"

AEntities::AEntities( )
{

}

AEntities::~AEntities( )
{

}

void	AEntities::update( time_t dt )
{
	(void)dt;
}

int		AEntities::coordX( void )
{
	return (this->_x);
}

int		AEntities::coordY( void )
{
	return (this->_x);
}

AEntities::AEntities(int height, int width, std::list<AEntities *> list_ent, std::list<std::pair<int, int> > snake_nodes)
{
	int		rnd_x;
	int		rnd_y;
	bool	set;

	//Too slow and freeze game with big snake
	set = false;
	while (!set)
	{
		srand (time(NULL));
		rnd_x = (rand() % width) + 0;
		rnd_y = (rand() %  height) + 0;
		if (!MapTools::cmpMap(list_ent, snake_nodes, rnd_x, rnd_y))
		{
			this->setX(rnd_x);
			this->setY(rnd_y);
			set = true;
		}
	}

/*	int		rnd_x;
	int		rnd_y;
	bool	set;

	//with recucivity
	set = false;
	while (!set)
	{
		srand (time(NULL));
		rnd_x = (rand() % width) + 0;
		rnd_y = (rand() %  height) + 0;
		if (MapTools::empty_place(width, height, list_ent, snake_nodes, &rnd_x, &rnd_y))
		{
			this->setX(rnd_x);
			this->setY(rnd_y);
			set = true;
		}
	}*/

/*
	//Algo with if fail a search with x and y
	int		rnd_x;
	int		rnd_y;
	bool	set;
	int		x_test;
	int		save_x;
	int		y_test;

	x_test = 0;
	y_test = 0;
	set = false;
	while (!set)
	{
		srand (time(NULL));
		rnd_x = (rand() % width) + 0;
		rnd_y = (rand() %  height) + 0;
		if (!MapTools::cmpMap(list_ent, snake_nodes, rnd_x, rnd_y))
		{
			this->setX(rnd_x);
			this->setY(rnd_y);
			set = true;
		}
		else
		{
			save_x = rnd_x;
			while (x_test < width)
			{
				rnd_x = x_test;
				if (!MapTools::cmpMap(list_ent, snake_nodes, rnd_x, rnd_y))
				{
					this->setX(rnd_x);
					this->setY(rnd_y);
					set = true;
					break ;
				}
			}

			if (set != true)
			{
				while (y_test < height)
				{
					rnd_y = y_test;
					if (!MapTools::cmpMap(list_ent, snake_nodes, save_x, rnd_y))
					{
						this->setX(save_x);
						this->setY(rnd_y);
						set = true;
						break ;
					}
				}
			}
		}
	}*/
}

AEntities::AEntities( AEntities const & rhs )
{
	*this = rhs;
}



AEntities & AEntities::operator=( AEntities const & rhs )
{
	this->_x = rhs.getX();
	this->_y = rhs.getY();
	this->_duration = rhs.getDuration();
	this->_score = rhs.getScore();
	this->_collidable = rhs.getCollidable();
	return (*this);
}

/* GETTERS & SETTERS */
void			AEntities::setX(int x) {this->_x = x;}
void			AEntities::setY(int y) {this->_y = y;}
void			AEntities::setDuration(float duration) {this->_duration = duration;}
void			AEntities::setScore(int score) {this->_score = score;}
void			AEntities::setCollidable(bool collidable) {this->_collidable = collidable;}
int				AEntities::getX() const { return (this->_x); }
int				AEntities::getY() const { return (this->_y); }
float			AEntities::getDuration() const { return (this->_duration); }
int				AEntities::getScore() const { return (this->_score); }
bool			AEntities::getCollidable() const { return (this->_collidable); }
