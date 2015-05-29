/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AEntities.class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/28 16:55:27 by larry             #+#    #+#             */
/*   Updated: 2015/05/29 04:46:36 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "AEntities.class.hpp"

AEntities::AEntities(int x, int y, float duration, int score, bool collidable)
{
	this->setX(x);
	this->setY(y);
	this->setDuration(duration);
	this->setScore(score);
	this->setCollidable(collidable);

}
AEntities::AEntities( AEntities const & rhs )
{
	*this = rhs;
}

virtual AEntities::AEntities( Game const mygame )
{
	int		rnd_x;
	int		rnd_y;
	bool	set;

	while (!set)
	{
		srand (time(NULL));
		rnd_x = rand() % mygame->getWidth() + 0;
		rnd_y = rand() % mygame->getHeight() + 0;
		if (!mygame->mapCmpSnake(rnd_x, rnd_y) && !mygame->mapCmpEnt(rnd_x, rnd_y))
		{
			this->setX(x);
			this->setY(y);
			set = true;
		}
	}
	mygame->addEntities(*this);
}

AEntities & AEntities::operator=( AEntities const & rhs )
{
	this->_x = rhs.getX();
	this->_y = rhs.getY();
	this->_duration = rhs.getDuration();
	this->_score = rhs.getScore();
	this->_collidable = rhs.getCollidable();
}

/* GETTERS & SETTERS */
void			AEntities::setX(int x) {this->_x = x}
void			AEntities::setY(int y) {this->_y = y}
void			AEntities::setDuration(float duration) {this->_duration = duration}
void			AEntities::setScore(int score) {this->_score = score}
void			AEntities::setCollidable(bool collidable) {this->_collidable = collidable}
int				AEntities::getX() const { return (this->_x); }
int				AEntities::getY() const { return (this->_y); }
float			AEntities::getDuration() const { return (this->_duration); }
int				AEntities::getScore() const { return (this->_score); }
bool			AEntities::getCollidable() const { return (this->_collidable); }
