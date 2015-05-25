#ifndef GETOPT_HPP
# define GETOPT_HPP

# include <map>
# include <iostream>

class Gettest
{
public:
	Gettest(  );
	Gettest( char *value, std::string test);
	Gettest( Gettest const & _ );
	virtual ~Gettest(  );

	Gettest &	operator=( Gettest const & _ );

	/* Setters & getters */
	void		setValue( char *value );
	void		setTest( std::string test );

	char*						getValue() const;
	std::string					getTest() const;

	std::string					makeTest( char *value, std::string test );

private:
	char*						_value;
	std::string					_test;

	/* check if value is an unsigned int */
	std::string					is_unsigned_int();

	/* check if lenght value is above the max set : max[<my max>] */
	std::string					max();

	/* check if lenght value is under the min set : max[<my max>] */
	std::string					min();
};

#endif
