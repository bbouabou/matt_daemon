#include "Tintin_reporter.h"
#include "matt_daemon.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iomanip> 
#include <sstream> 
#include <string>

Tintin_reporter::Tintin_reporter()
{

}

void Tintin_reporter::record(std::string const &message, std::string const &type)
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    std::string outputStr = "[" + zeroPadNumber(timePtr->tm_mday) + "/" + zeroPadNumber((timePtr->tm_mon)+1) + "/" + zeroPadNumber((timePtr->tm_year)+1900)
              + "-" + zeroPadNumber(timePtr->tm_hour) + ":" + zeroPadNumber(timePtr->tm_min) + ":" + zeroPadNumber(timePtr->tm_sec) + "] "
              + "[" + type + "] - "
              + message;

    //May comment
    std::cout << outputStr.c_str() << std::endl;

    //Lets check if folders LOG PATH are there
    struct stat info;
    if( stat( LOG_PATH, &info ) != 0 )
    {
        std::string mkDirStr = "mkdir -p " LOG_PATH;
        system(mkDirStr.c_str());
    }

    static std::ofstream outfile(LOG_FILE, std::ios_base::out | std::ios_base::app);
    if (outfile)
    {
        outfile << outputStr.c_str() << std::endl;
    }

}

std::string Tintin_reporter::zeroPadNumber(int num)
{
    std::ostringstream ss;
    ss << std::setw(2) << std::setfill( '0' ) << num;
    return ss.str();
}