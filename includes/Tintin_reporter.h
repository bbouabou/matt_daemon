#ifndef TINTIN_REPORTER_H
# define TINTIN_REPORTER_H

# include <iostream>
# include <fstream>
# include <istream>
# include <sstream>

# include <ctime>
# include <time.h>

# include <string>
# include <iomanip>

# include <sys/types.h>
# include <sys/stat.h>

class Tintin_reporter
{

    public:
        Tintin_reporter(void);
        Tintin_reporter(Tintin_reporter const & src);
        virtual ~Tintin_reporter(void);
        Tintin_reporter & operator=(Tintin_reporter const & rhs);
        
        static void record(std::string const &message, std::string const &type);
        static std::string zeroPadNumber(int nb);

};

#endif // TINTIN_REPORTER_H
