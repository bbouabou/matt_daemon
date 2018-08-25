#include <iostream>
#include "CDaemon.h"
#include "Tintin_reporter.h"

using namespace std;

int main()
{
    CDaemon daemon;

    daemon.startServer();
    daemon.run();

    return 0;
}
