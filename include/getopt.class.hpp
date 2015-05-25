#ifndef GETOPT_HPP
# define GETOPT_HPP

# include <map>
# include <vector>
# include <iostream>
# include <functional>

/*	Allow test inside check() method */
# include "gettest.class.hpp"

class Getopt
{
public:
	Getopt( int argc, char **argv);
	Getopt( Getopt const & _ );
	virtual ~Getopt(  );

	Getopt &	operator=( Getopt const & _ );

	/* Setters & getters */
	void		setLimit( int max );
	void		setArgc( int argc );
	void		setArgv( char **argv );
	void		setError( std::string error );

	std::map<int, std::string>	getOpts() const;
	int							getLimit() const;
	int							getArgc() const;
	char**						getArgv() const;
	std::string					getError() const;

	/* Add rules to one of cell in argv (cf. Getopt.doc.txt)*/
	bool		addRules( int nbarg, std::string opts );

	/* Try to test each arguments with addRules() setting */
	bool		check();

	/* Catch error from check() or early and display it */
	void		error();

	/* Display rules of argv one by one*/
	void		readOpt();


private:
	std::map<int, std::string>	_opt;
	char**						_argv;
	int							_argc;
	int							_limit;
	std::string					_error;

	Getopt(  );
};

#endif
