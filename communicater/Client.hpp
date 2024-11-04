#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

class Client {
	public:
		Client(int port, std::string hostname);
		~Client();
		int sendMsg(std::string p);
		int recvMsg(std::string p);

	protected:
		int makeSocket();
		int getHostByName(std::string hostname);
		int setServInfo(int port);
		int connect();

	private:
		int _sockfd;
		struct hostent *_serverinfo;
		struct sockaddr_in _serv_addr;
		char _buf[256];
};

