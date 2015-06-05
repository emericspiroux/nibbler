/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettest.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 03:15:32 by larry             #+#    #+#             */
/*   Updated: 2015/06/02 15:45:35 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETTEST_HPP
# define GETTEST_HPP

# include <map>
# include <iostream>
# include <vector>
# include <cstring>
# include <string>
# include <stdlib.h>
# include <sstream>
# include <ctype.h>
# include <fstream>

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
	void		setFct( std::string test );

	char*						getValue() const;
	std::string					getFct() const;

	/* make test according fct and value */
	std::string					makeTest( char *value, std::string test );

	/* fct of boostlib who split a string in multiple string in a vector according char delimiter */
	std::vector<std::string>	split(std::string str, char delimiter);

private:
	char*						_value;
	std::string					_fct;

	/* check if value is an unsigned int */
	std::string					getParam();

	/* check if value is an unsigned int */
	std::string					is_unsigned_int();

	/* check if lenght value is above the max set : max[<my max>] */
	std::string					max();

	/* check if lenght value is under the min set : max[<my max>] */
	std::string					min();

	/* check if it's number */
	std::string					is_numeric();
};

#endif
