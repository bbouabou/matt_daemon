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
    CDaemon daemon;

    if (daemon.init())
    {
        daemon.startServer();
        daemon.run();
    }
    return 0;
}
