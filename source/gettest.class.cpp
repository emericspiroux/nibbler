/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettest.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larry <larry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 14:12:31 by larry             #+#    #+#             */
/*   Updated: 2015/05/25 18:53:43 by larry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "gettest.class.hpp"

Gettest::~Gettest()
{
}

Gettest::Gettest()
{
}

Gettest::Gettest( Gettest const & rhs )
{
	*this = rhs;
}

Gettest &	Gettest::operator=( Gettest const & rhs )
{
	this->_value = rhs.getValue();
	this->_fct = rhs.getFct();
	return (*this);
}

/* Setters & getters */
void		Gettest::setValue( char *value ) { this->_value = value; }

void		Gettest::setFct( std::string test ) { this->_fct = test; }


char*						Gettest::getValue() const { return this->_value; }

std::string					Gettest::getFct() const { return this->_fct; }

/* make test according fct and value */
std::string					Gettest::makeTest( char *value, std::string test )
{
	std::string ret;

	this->setValue(value);
	this->setFct(test);
	if ((test.find("max[", 0)) != std::string::npos)
		ret += this->max();
	if ((test.find("unsigned_int", 0)) != std::string::npos)
		ret += this->is_unsigned_int();
	if ((test.find("is_numeric", 0)) != std::string::npos)
		ret += this->is_numeric();
	return (ret);
}

/* check if value is an unsigned int */
std::string					Gettest::is_unsigned_int()
{
	unsigned long a;
	std::string   ret;

	ret += this->is_numeric();
	try
	{
		a = strtoul(this->_value, nullptr, 0);
		return ("");
	}
    catch (const std::out_of_range& oor)/* above 4 294 967 295 */
    {
    	return ((ret += "Gettest : error : Argument are not an unsigned int.\n"));
    }
}

/* check if value is an unsigned int */
std::string					Gettest::getParam()
{
	std::vector<std::string>	v;
	size_t						end;

	if (this->_fct.empty())
	{
		std::cout << "Gettest: error : Bad Format for test \"" << this->_value << "\".\n";
		exit(1);
	}
	if ((v = this->split(this->_fct, '[')).empty())
	{
		std::cout << "Gettest: error : Bad Format for test \"" << this->_value << "\".\n";
		exit(1);
	}
	end = v[1].length();
	v[1][end - 1] = '\0';
	return (v[1]);
}

/* check if lenght value is above the max set : max[<my max>] */
std::string					Gettest::max()
{
	int				max;
	std::string		ret;

	max = std::stoi(this->getParam());
	if (std::strlen(this->_value) < (size_t)max)
		return ("");
	else
	{
		ret = "Gettest : error : lenght of Argument \"";
		ret += this->getValue();
		ret += "\" must be under ";
		ret += std::to_string(max);
		ret += ".\n";
    	return (ret);
	}
}

/* check if lenght value is under the min set : max[<my max>] */
std::string					Gettest::min()
{
	int				min;
	std::string		ret;

	min = std::stoi(this->getParam());
	if (std::strlen(this->_value) >= (size_t)min)
		return ("");
	else
	{
		ret = "Gettest : error : lenght of Argument \"";
		ret += this->getValue();
		ret += "\" must be above ";
		ret += min;
		ret += ".\n";
		return (ret);
	}
}

/* check if it's number */
std::string					Gettest::is_numeric()
{
	unsigned int			i;
	std::string		ret;

	i = 0;
	while (this->_value[i])
	{
		if (std::isalpha(this->_value[i]))
		{
			ret = "Gettest : error : Argument \"";
			ret += this->_value;
			ret += "\" Must be numeric.\n";
			return (ret);
		}
		i++;
	}
	return ("");
}

std::vector<std::string> 	Gettest::split(std::string str, char delimiter)
{
	std::vector<std::string> internal;
	std::stringstream ss(str);
	std::string tok;

	while(getline(ss, tok, delimiter)) {
		internal.push_back(tok);
	}

	return (internal);
}
