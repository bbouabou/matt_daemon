#include "CDaemon.h"
#include "Tintin_reporter.h"
#include "matt_daemon.h"
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>

CDaemon::CDaemon()
{
    Tintin_reporter::record("Constructor", "LOG");
}

bool CDaemon::init()
{
    Tintin_reporter::record("init", "LOG");

    //Lets check if folders LOCK_PATH exists
    struct stat info;
    if( stat( LOCK_FILE_PATH, &info ) != 0 )
    {
        std::string mkDirStr = "mkdir -p " LOCK_FILE_PATH;
        system(mkDirStr.c_str());
    }

    //Lets create and lock file
    std::string lockFileStr(LOCK_FILE_PATH);
    lockFileStr+=LOCK_FILE;
    _lockFilefd = open(lockFileStr.c_str(), O_RDWR | O_CREAT, 0666);
    int returnCode = flock(_lockFilefd, LOCK_EX | LOCK_NB);
    if (returnCode)
    {
        Tintin_reporter::record("Locked ... cannot init daemon","ERROR");
        return false;
    }


    //Lets initialize our socket
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    _serverSin.sin_addr.s_addr = htonl(INADDR_ANY);
    _serverSin.sin_family = AF_INET;
    _serverSin.sin_port = htons(4242);
    return true;
}

void CDaemon::startServer()
{
    Tintin_reporter::record("startServer", "INFO");

    if (SOCKET_ERROR == bind(_serverSocket, (SOCKADDR*)&_serverSin, sizeof(_serverSin)))
        Tintin_reporter::record("Error on bind", "ERROR");


    if (SOCKET_ERROR == listen(_serverSocket, MAX_NB_CLIENT))
        Tintin_reporter::record("Error on listen", "ERROR");
}

void CDaemon::stopServer()
{
    Tintin_reporter::record("stopServer", "INFO");

    if (SOCKET_ERROR == closesocket(_serverSocket))
        Tintin_reporter::record("Error on close", "ERROR");

    int returnCode = flock(_lockFilefd, LOCK_UN);
    if (returnCode)
    {
        Tintin_reporter::record("Cannot unlock file","ERROR");
    }
}

void CDaemon::run()
{
    Tintin_reporter::record("run", "LOG");

    /* Socket et contexte d'adressage du client */
    SOCKADDR_IN csin;
    SOCKET clientSocket;
    socklen_t crecsize = sizeof(csin);

    socklen_t taille = sizeof(csin);

    while (42)
    {
        clientSocket = accept(_serverSocket, (SOCKADDR*)&csin, &taille);

        Tintin_reporter::record("New client connected", "INFO");

        /*if ((pid = fork()) == -1)
        {
            close(clientSocket);
            continue;
        }
        else if(pid > 0)
        {
            close(clientSocket);
            counter++;
            printf("here2\n");
            continue;
        }
        else if(pid == 0)
        {
            char buf[100];

            counter++;
            printf("here 1\n");
            close(clientSocket);
            break;
        }*/
    }
}
