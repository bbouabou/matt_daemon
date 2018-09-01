#include <iostream>
#include "CDaemon.h"
#include "Tintin_reporter.h"

using namespace std;

int main()
{

	if (getuid()) {
		std::cout << "This program requires root privileges" << std::endl;
        exit(1);
    }
    CDaemon *daemon = CDaemon::instance();

    if (daemon->init())
    {
        if (daemon->startServer())
            daemon->run();
    }
    free(daemon);
    return 0;
}
