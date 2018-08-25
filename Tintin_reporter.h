#ifndef TINTIN_REPORTER_H
#define TINTIN_REPORTER_H
#include <iostream>
#include <fstream>
#include <istream>
#include <ctime>
#include <time.h>
#include <string>

#define LOG_FILE "/var/log/matt_daemon/matt_daemon.log"
#define LOG_PATH "/var/log/matt_daemon/"

class Tintin_reporter
{

public:
    Tintin_reporter();

    static void record(std::string const &message, std::string const &type);
};

#endif // TINTIN_REPORTER_H
