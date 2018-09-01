#include "CDaemon.h"
#include "Tintin_reporter.h"
#include "matt_daemon.h"

CDaemon *CDaemon::_singleton = nullptr;

CDaemon *CDaemon::instance()
{
    // instance unique
    if (!_singleton)
        _singleton = new CDaemon;
    return _singleton;
}

CDaemon::CDaemon()
{
}


CDaemon::CDaemon (CDaemon const & src)
{
	*this = src;
}

CDaemon& CDaemon::operator=(CDaemon const &rhs)
{
	if (this != &rhs)
	{
		this->_serverSocket = rhs.getServerSocket();
		this->_serverSin = rhs.getServerSin();
		this->_lockFilefd = rhs.getLockFileFd();
		this->_countClient = rhs.getCountClient();
		this->_fds = rhs.getFds();
	}
	return (*this);
}

SOCKET	CDaemon::getServerSocket(void) const
{
	return (this->_serverSocket);
}

SOCKADDR_IN	CDaemon::getServerSin(void) const
{
	return (this->_serverSin);
}

int	CDaemon::getLockFileFd(void) const
{
	return (this->_lockFilefd);
}

int	CDaemon::getCountClient(void) const
{
	return (this->_countClient);
}

std::vector<int> CDaemon::getFds(void) const
{
	return (this->_fds);
}

bool CDaemon::init()
{
    Tintin_reporter::record("init", "LOG");

    pid_t pid, s_sid;

    if ((pid = fork()) == -1)
    {
        Tintin_reporter::record("Error fork fails !", "ERROR");
        return false;
    }
    else if (pid > 0)
        return(0);
    umask(0);
    s_sid = setsid();
    if (s_sid == -1)
    {
        Tintin_reporter::record("Error setsid fails !", "ERROR");
        Tintin_reporter::record(std::strerror(errno), "ERROR");
        return false;
    }

    //Lets check if folders LOCK_PATH exists
    struct stat info;
    if (stat(LOCK_FILE_PATH, &info) != 0)
    {
        std::string mkDirStr = "mkdir -p " LOCK_FILE_PATH;
        system(mkDirStr.c_str());
    }

    //Lets create and lock file
    std::string lockFileStr(LOCK_FILE_PATH);
    lockFileStr += LOCK_FILE;
    _lockFilefd = open(lockFileStr.c_str(), O_RDWR | O_CREAT, 0644);
    int returnCode = flock(_lockFilefd, LOCK_EX | LOCK_NB);
    if (returnCode)
    {
        Tintin_reporter::record("Locked ... cannot init daemon", "ERROR");
        std::cout << "Locked ... cannot init daemon" << std::endl;
        return false;
    }

    //Lets initialize our socket
    if ((_serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        Tintin_reporter::record("Could not create socket", "ERROR");
        std::cout << "Could not create socket" << std::endl;
        return false;
    }
    int sock_opt = 1;
    if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, (void*)&sock_opt, sizeof(sock_opt)) < 0)
    {
        Tintin_reporter::record("setsockopt failed", "ERROR");
        std::cout << "setsockopt failed" << std::endl;
        return false; 
    }
    _serverSin.sin_addr.s_addr = htonl(INADDR_ANY);
    _serverSin.sin_family = AF_INET;
    _serverSin.sin_port = htons(PORT);
    chdir("/");
    return true;
}

bool CDaemon::startServer()
{
    Tintin_reporter::record("startServer", "INFO");

    if (SOCKET_ERROR == bind(_serverSocket, (SOCKADDR *)&_serverSin, sizeof(_serverSin)))
    {
        Tintin_reporter::record("Error on bind", "ERROR");
        Tintin_reporter::record(std::strerror(errno), "ERROR");        
        return false;
    }

    if (SOCKET_ERROR == listen(_serverSocket, MAX_NB_CLIENT))
    {
        Tintin_reporter::record("Error on listen", "ERROR");
        return false;
    }

    for (int i = 1; i < _NSIG; i++)
        signal(i, catchedSignal);

    return true;
}

void CDaemon::stopServer()
{
    for (std::vector<int>::iterator it = _fds.begin(); it != _fds.end(); ++it)
    {
        close(*it);
    }
    Tintin_reporter::record("Exiting ... ", "INFO");

    if (SOCKET_ERROR == close(_serverSocket))
        Tintin_reporter::record("Error on close", "ERROR");

    int returnCode = flock(_lockFilefd, LOCK_UN);
    if (returnCode)
    {
        Tintin_reporter::record("Cannot unlock file", "ERROR");
    }
    std::string lockFileStr(LOCK_FILE_PATH);
    lockFileStr += LOCK_FILE;
    if (remove(lockFileStr.c_str()) != 0)
    {
        Tintin_reporter::record("Cannot delete file", "ERROR");
    }
}

void CDaemon::run()
{
    Tintin_reporter::record("run", "LOG");

    /* Socket et contexte d'adressage du client */
    SOCKADDR_IN csin;
    int fd = 0;

    socklen_t lenght = sizeof(csin);

    while (42)
    {
        if ((fd = accept(_serverSocket, (SOCKADDR *)&csin, &lenght)) == -1)
        {
            Tintin_reporter::record("error accepting client", "ERROR");
        }
        if (_countClient < MAX_NB_CLIENT)
        {
            _countClient++;
            _fds.push_back(fd);
            std::thread thread(CDaemon::startClient, fd, this);
            thread.detach();
        }
        else
        {
            Tintin_reporter::record("A client tried to connect but no space left on the queue", "LOG");
            close(fd);
        }
    }
}

void CDaemon::startClient(int fd, CDaemon *daemon)
{
    Tintin_reporter::record("New client connected", "INFO");
    int response;
    char buff[BUFFER_SIZE + 1];
    while (42)
    {
        bzero(&buff, BUFFER_SIZE);
        response = recv(fd, buff, BUFFER_SIZE, 0);
        if (response > 0)
        {
            std::string content = buff;
            content.erase(std::remove(content.begin(), content.end(), '\n'), content.end());
            Tintin_reporter::record(content, "LOG");
            if (!content.compare("quit"))
            {
                daemon->stopServer();
                free(CDaemon::instance());
                exit(0);
            }
        }
        else
        {
            Tintin_reporter::record("Client has been disconnected from the server", "INFO");
            daemon->removeClient(fd);
            break;
        }
    }
}

void CDaemon::decrementCounter(void)
{
    _countClient--;
}

void CDaemon::removeClient(int fd)
{
    _fds.erase(std::remove(_fds.begin(), _fds.end(), fd), _fds.end());
    decrementCounter();
    close(fd);
}

void CDaemon::catchedSignal(int signal)
{
    CDaemon::instance()->stopServer();
    Tintin_reporter::record("signal: " + std::to_string(signal), "SIGNAL");
    free(CDaemon::instance());
    exit(signal);
}


CDaemon::~CDaemon()
{
}
