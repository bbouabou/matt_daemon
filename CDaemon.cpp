#include "CDaemon.h"
#include "Tintin_reporter.h"

CDaemon::CDaemon()
{
    Tintin_reporter::record("Constructor", "LOG");
}

void CDaemon::init()
{
    Tintin_reporter::record("init", "LOG");


}

void CDaemon::run()
{
    Tintin_reporter::record("run", "LOG");

}

void CDaemon::startServer()
{
    Tintin_reporter::record("startServer", "INFO");

}

void CDaemon::stopServer()
{
    Tintin_reporter::record("stopServer", "INFO");

}
