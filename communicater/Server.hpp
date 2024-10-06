
#pragma once

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>	

class Server {
	public:
	protected:
	private:
		int		sockfd;
		struct sockaddr_in	serv_addr;
		std::vector	client_list;

		bool	makeSocket(unsigned int port);
		bool	sendMsg(char *msg);
		bool	closeConnection();

}

