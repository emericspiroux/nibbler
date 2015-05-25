#include <iostream>
#include "nibbler.hpp"

int		main( int argc, char **argv )
{
	Getopt verif(argc, argv);

	verif.setLimit(3);
	verif.addRules( 1, "unsigned_int|max[10]");
	verif.addRules( 2, "unsigned_int|max[10]");
	if (!verif.check())
		verif.error();
	verif.readOpt();
	std::cout << "All's right!" << std::endl;
	return (0);
}
