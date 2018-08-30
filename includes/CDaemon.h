#ifndef CDAEMON_H
# define CDAEMON_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)
#define BUFFER_SIZE 2048

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

class CDaemon
{
public:
    CDaemon();

    bool init();
    void startServer();
    void run();
    void stopServer();
    void decrementCounter();
    void removeClient(int fd);
    static void startClient(int fd, CDaemon *daemon);
    static void catchedSignal(int signal);

private:
    SOCKET _serverSocket;
    SOCKADDR_IN _serverSin;
    int _lockFilefd;
    int _countClient = 0;
	std::vector<int> _fds;
};

#endif // CDAEMON_H
