#ifndef LIBFTCURSE_HPP
# define LIBFTCURSE_HPP

# include "IDisplayLib.hpp"

class CurseGraphics: public IDisplayLib
{
public:
	CurseGraphics(  );
	CurseGraphics( CurseGraphics const & _ );
	virtual ~CurseGraphics(  );

	CurseGraphics &	operator=( CurseGraphics const & _ );

	void			introduce( void ) const;

	std::string		getName( void ) const;

private:
	std::string		_name;
};

extern "C" {

	CurseGraphics	*createGraphic( void );

	void			deleteGraphic( CurseGraphics *graphics );

}

#endif
