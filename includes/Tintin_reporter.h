#ifndef TINTIN_REPORTER_H
# define TINTIN_REPORTER_H
#include <iostream>
#include <fstream>
#include <istream>
#include <ctime>
#include <time.h>
#include <string>

class Tintin_reporter
{

public:
    Tintin_reporter();

    static void record(std::string const &message, std::string const &type);
    static std::string zeroPadNumber(int nb);

};

#endif // TINTIN_REPORTER_H
