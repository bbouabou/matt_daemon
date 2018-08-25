#include "Tintin_reporter.h"
#include <sys/types.h>
#include <sys/stat.h>

Tintin_reporter::Tintin_reporter()
{

}

void Tintin_reporter::record(std::string const &message, std::string const &type)
{
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    std::string outputStr = "[" + std::to_string(timePtr->tm_mday) + "/" + std::to_string((timePtr->tm_mon)+1) + "/" + std::to_string((timePtr->tm_year)+1900)
              + "-" + std::to_string(timePtr->tm_hour) + ":" + std::to_string(timePtr->tm_min) + ":" + std::to_string(timePtr->tm_sec) + "] "
              + "[" + type + "] - "
              + message;

    std::cout << outputStr.c_str() << std::endl;

#ifdef unix
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
#endif

}
