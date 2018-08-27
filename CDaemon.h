#ifndef CDAEMON_H
#define CDAEMON_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

class CDaemon
{
public:
    CDaemon();

    bool init();
    void startServer();
    void stopServer();
    void run();

private:
    SOCKET _serverSocket;
    SOCKADDR_IN _serverSin;
    int _lockFilefd;

};

#endif // CDAEMON_H
