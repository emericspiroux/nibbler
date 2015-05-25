#include <iostream>
#include "nibbler.hpp"

int		main( int argc, char **argv )
{
	Getopt verif(argc, argv);

	verif.setLimit(3);
	verif.addRules( 1, "unsigned_int|max[10]|is_numeric|no_neg");
	verif.addRules( 2, "unsigned_int|max[10]|is_numeric|no_neg");
	if (!verif.check())
		verif.myUsage("nibbler_usage");
	std::cout << "All's right!" << std::endl;
	return (0);
}
