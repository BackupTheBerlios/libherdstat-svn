#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <iostream>
#include <cstdlib>
#include <herdstat/exceptions.hh>
#include <herdstat/util/progress.hh>
#include <unistd.h>

int
main(int argc, char **argv)
{
	std::string type("percent");

	if (argc == 2)
		type.assign(argv[1]);
	else if (argc != 1)
	{
		std::cerr
		    << "usage: progress <type>"
		    << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		herdstat::util::Progress progress(type);
		progress.start(1000, "Some operation");
		for (size_t i = 0 ; i < 1000 ; ++i)
		{
			++progress;
			sleep(1);
		}
	}
	catch (const herdstat::BaseException& e)
	{
		std::cerr << "Oops!\n  * " << e.backtrace(":\n	* ")
		    << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=8 ts=8 sts=8 fdm=marker noet : */
