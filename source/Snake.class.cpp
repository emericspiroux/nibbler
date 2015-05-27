# include "Snake.class.hpp"

Snake::Snake(  ){}

Snake::Snake( game _game )
{
	this->setGame(_game);
}

Snake::Snake( Snake const & rhs )
{
	*this = rhs;
}

Snake &	Snake::operator=( Snake const & rhs )
{
	this->_nodes = rhs.getNodes();
	this->_speed = rhs.getSpeed();
	this->_direction = rhs.getDirection();
	this->_last_direction = rhs.getLastDirection();
	this->_game = rhs.getGame();
	return (*this);
}

/* Getters & Setters */
void					Snake::setNodes(std::map<int, int> nodes) { this->_nodes = nodes}
void					Snake::setSpeed(float speed) { this->_speed = speed}
void					Snake::setDirection( int direction ) { this->_direction = direction}
void					Snake::setLastDirection(int last_direction) { this->_last_direction = last_direction}
void					Snake::setGame(Game c_game) { this->_game = game}

std::map<int, int>		Snake::getNodes() const { return (this->_nodes); }
float					Snake::getSpeed() const { return (this->_speed); }
int						Snake::getDirection() const { return (this->_direction); }
int						Snake::getLastDirection() const { return (this->_last_direction); }
Game					Snake::getGame() const { return (this->_game);}

void				Snake::update( float dt )
{
	//Si pas fin du jeu.
		//Si dt > DT_MACRO
			//avancer la tete
			//Mettre tout les noeuds a la place du suivant
			//Si le serpent a manger une entities 
				//Fin du jeu si collisable
				//Sinon si Miam qqch, Ajout d'un morceau et des points
		//FinSi
	//FinSi
}

void				Snake::add_node()
{
	//Si il y a aucune entities 
		//ajout d'une morceau a la fin
	//FinSi
}