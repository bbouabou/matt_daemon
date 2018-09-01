#ifndef CDAEMON_H
# define CDAEMON_H


# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <thread>
# include <signal.h>

# include <vector>
# include <algorithm>

# include <string>
# include <cstring>

# include <sys/file.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/socket.h>

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
# define BUFFER_SIZE 2048

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

class CDaemon
{
public:
    CDaemon(void);
    CDaemon(CDaemon const & src);
    virtual ~CDaemon(void);
    CDaemon & operator=(CDaemon const & rhs);

    static CDaemon *instance(void);
    bool init(void);
    bool startServer(void);
    void run(void);
    void stopServer(void);
    void decrementCounter(void);
    void removeClient(int fd);
    static void startClient(int fd, CDaemon *daemon);
    static void catchedSignal(int signal);
    SOCKET	getServerSocket(void) const;
    SOCKADDR_IN	getServerSin(void) const;
    int	getLockFileFd(void) const;
    int	getCountClient(void) const;
    std::vector<int> getFds(void) const;

private:
    SOCKET _serverSocket;
    SOCKADDR_IN _serverSin;
    int _lockFilefd;
    int _countClient = 0;
	std::vector<int> _fds;
    static CDaemon* _singleton;
};

#endif // CDAEMON_H
