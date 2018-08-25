#include "CDaemon.h"
#include "Tintin_reporter.h"

CDaemon::CDaemon()
{
    Tintin_reporter::record("Constructor", "LOG");
}

void CDaemon::init()
{
    Tintin_reporter::record("init", "LOG");

    _socket = socket(AF_INET, SOCK_STREAM, 0);

    _sin.sin_addr.s_addr = htonl(INADDR_ANY);
    _sin.sin_family = AF_INET;
    _sin.sin_port = htons(4242);
}

void CDaemon::startServer()
{
    init();

    Tintin_reporter::record("startServer", "INFO");

    if (SOCKET_ERROR == bind(_socket, (SOCKADDR*)&_sin, sizeof(_sin)))
        Tintin_reporter::record("Error on bind", "LOG");


    if (SOCKET_ERROR == listen(_socket, MAX_NB_CLIENT))
        Tintin_reporter::record("Error on listen", "LOG");
}

void CDaemon::stopServer()
{
    Tintin_reporter::record("stopServer", "INFO");

    if (SOCKET_ERROR == closesocket(_socket))
        Tintin_reporter::record("Error on close", "LOG");
}

void CDaemon::run()
{
    Tintin_reporter::record("run", "LOG");

    /* Socket et contexte d'adressage du client */
    SOCKADDR_IN csin;
    SOCKET clientSocket;
    socklen_t crecsize = sizeof(csin);

    socklen_t taille = sizeof(csin);
    clientSocket = accept(_socket, (SOCKADDR*)&csin, &taille);

    Tintin_reporter::record("client connected", "INFO");
}
