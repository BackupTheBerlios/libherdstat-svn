#include <iostream>
#include <string>
#include <cstdlib>
#include <herdstat/fetcher/fetcher.hh>

using namespace herdstat;

int
main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "usage: fetch <implementation> <url> <path>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string imp(argv[1]);
    std::string url(argv[2]);
    std::string path(argv[3]);

    try
    {
        FetcherOptions opts;
        opts.set_implementation(imp);
        opts.set_verbose(true);

        Fetcher fetch(opts);
        fetch(url, path);
    }
    catch (const FetchException& e)
    {
        std::cerr << "Failed to save '" << url << "' to '"
            << path << "." << std::endl;
        return EXIT_FAILURE;
    }
    catch (const BaseException& e)
    {
        std::cerr << "Oops!\n  * " << e.backtrace(":\n  * ")
            << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* vim: set tw=80 sw=4 fdm=marker et : */
