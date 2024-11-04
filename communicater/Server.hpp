
#pragma once

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>

#include <string>

class Server {
	public:
		Server(unsigned int port);
		~Server();
		bool	makeSocket(unsigned int port);
		int		writePoll();
		int		readPoll();
		int		connectNewClient();
		int		recvMsg(int clifd);
		bool	sendMsg(unsigned int cli_fd, const char *msg, size_t len);
		bool	closeConnection(unsigned int fd);
		int		mainLoop();
	protected:
	private:
		fd_set	_fds;
		int		_sockfd;
		int		_clifd;
		struct sockaddr_in	_serv_addr;
		struct sockaddr_in	_cli_addr;
		char _recv_data[256];

		bool	_write_flag;
		std::string	_write_content;

		struct timeval _tv;
		size_t	_listen_queue = 10;
};
