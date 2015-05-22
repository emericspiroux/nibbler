#ifndef LIB_HPP
# define LIB_HPP

# include "ilib.hpp"

class Graphics: public IGraphics
{
public:
	Graphics(  );
	Graphics( Graphics const & _ );
	virtual ~Graphics(  );

	Graphics &	operator=( Graphics const & _ );

	void	introduce( void ) const;

	std::string		getName( void ) const;

private:
	std::string	_name;
};

extern "C" {

	Graphics	*createGraphic( void );

	void		deleteGraphic( Graphics *graphics );

}

#endif
