#ifndef CDAEMON_H
#define CDAEMON_H

#ifdef unix
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
#endif

#define MAX_NB_CLIENT 3
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

    void init();
    void startServer();
    void stopServer();
    void run();

private:
    SOCKET _socket;
    SOCKADDR_IN _sin;

};

#endif // CDAEMON_H
