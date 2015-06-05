/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 14:12:31 by larry             #+#    #+#             */
/*   Updated: 2015/06/02 17:46:29 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "getopt.class.hpp"

Getopt::~Getopt()
{
}

Getopt::Getopt( int argc, char **argv)
{
	this->_argc = argc;
	this->_argv = argv;
	this->_limit = 0;
}

Getopt::Getopt( Getopt const & rhs )
{
	*this = rhs;
}

Getopt &	Getopt::operator=( Getopt const & rhs )
{
	this->_opt = rhs.getOpts();
	this->_argc = rhs.getArgc();
	this->_argv = rhs.getArgv();
	this->_limit = rhs.getLimit();
	this->_error = rhs.getError();
	return (*this);
}

/* Setters & getters */
void		Getopt::setLimit( int max ) { this->_limit = max; }

void		Getopt::setArgc( int argc ) { this->_argc = argc; }

void		Getopt::setArgv( char **argv ) { this->_argv = argv; }

void		Getopt::setError( std::string error ) { this->_error = error; }


std::map<int, std::string>		Getopt::getOpts() const { return this->_opt; }

int								Getopt::getLimit() const { return this->_limit; }

int								Getopt::getArgc() const { return this->_argc; }

char**							Getopt::getArgv() const { return this->_argv; }

std::string						Getopt::getError() const { return this->_error; }


/* Add rules to one of cell in argv (cf. Getopt.doc.txt)*/
bool		Getopt::addRules( int nbarg, std::string opts )
{
	if (nbarg > this->_limit)
	{
		this->_error += "Rules \"" + opts + "\" not Set.\n";
		return (false);
	}
	this->_opt.insert(std::pair<int, std::string>(nbarg, opts));
	return (true);
}

/* Try to test each arguments with addRules() setting */
bool		Getopt::check()
{
	std::map<int, std::string>::iterator it;
	std::vector<std::string> v;
	Gettest test;
	unsigned i;

	if (this->_limit <= 0)
	{
		this->_error += "Getopt : error : No limit set \n";
		return (false);
	}
	if (this->_limit != this->_argc)
	{
		this->_error += "Getopt : error : Must Contain ";
		this->_error += std::to_string(this->_limit);
		this->_error += " args.\n";
		return (false);
	}
	for (it=this->_opt.begin(); it!=this->_opt.end(); ++it)
	{
		v = test.split(it->second, '|');
		for( i = 0; !v[i].empty(); i++)
			this->_error += test.makeTest(this->_argv[it->first], v[i]);
	}

	if (!this->_error.empty())
		return (false);

	return (true);
}

/* Catch error from check() or early and display it */
void		Getopt::error()
{
	std::cout << _error;
	exit(0);
}

/* Display rules of argv one by one*/
void		Getopt::readOpt()
{
	std::map<int, std::string>::iterator it;

	std::cout << "Opt contains:\n";

	if (!this->_opt.empty())
		for (it=this->_opt.begin(); it!=this->_opt.end(); ++it)
			std::cout << it->first << " => " << it->second << std::endl;
	else
		std::cout << "Empty.\n";
}

/*	Display if exist usage in file give to function else display error*/
void		Getopt::myUsage(std::string filepath)
{
	std::string line;
  	std::ifstream myfile(filepath);
  	if ( myfile.is_open() )
  	{
  	  while ( getline (myfile,line) )
  	  {
  	    std::cout << line << '\n';
  	  }
  	  myfile.close();
  	}
  	else
  		this->error();
  	exit(0);
}
