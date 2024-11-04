
#include "Server.hpp"
#include "RingBuffer.hpp"

#include <csignal>
#include <string>
#include <iostream>
#include <iomanip>

#include <errno.h>
#include <fcntl.h>

Server::Server(unsigned int port)
{
	_tv.tv_sec = 0;
	_tv.tv_usec = 100000; // 100msec
	makeSocket(port);
	FD_ZERO(&_fds);
	_write_flag = false;

	std::signal(SIGPIPE, SIG_IGN);
}

Server::~Server()
{
	closeConnection(_clifd);
	close(_sockfd);
}

bool	Server::makeSocket(unsigned int port)
{
    // make a socket
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0) {
        perror("opening socket fails");
        return -1;
    }

    // provide address to the socket
    memset((char *)&_serv_addr, 0, sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = htons(port);
    if (bind(_sockfd, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0) {
        perror("binding fails");
        return -1;
    }

	// set fd non-blocking state
	int	flags = 0;
	if ((flags = fcntl(STDIN_FILENO, F_GETFL)) == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}
	flags |= O_NONBLOCK;
	if (fcntl(STDIN_FILENO, F_SETFL, flags) == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

	return true;
}

bool	Server::sendMsg(unsigned int cli_fd, const char *msg, size_t len)
{
	int n;
    n = send(cli_fd, msg, len, 0);
    if (n < 0) {
		perror("Server/sending failed");
        return false;
    }
	return true;
}

bool	Server::closeConnection(unsigned int fd)
{
	FD_CLR(fd, &_fds);
    close(fd);
	return true;
}

int	Server::writePoll()
{
	errno = 0;
	return select(1024, NULL, &_fds, NULL, &_tv); 
}

int	Server::readPoll()
{
	errno = 0;
	return select(1024, &_fds, NULL, NULL, &_tv); 
}

int Server::connectNewClient()
{
	struct sockaddr ad;
	unsigned int len;

	listen(_sockfd, 1);
	std::cout << "\tlisten success." << std::endl;
	_clifd = accept(_sockfd, &ad, &len);
	std::cout << "\taccept client." << std::endl;
	FD_SET(_clifd, &_fds);
	return 0;
}

int Server::recvMsg(int clifd)
{
	errno = 0;
	int recvsize = recv(clifd, &_buf[0], _RECV_SIZE, 0);
	if (errno == ECONNRESET)
		return -1;
	else if (recvsize < 0 && errno != EAGAIN) {
		perror("recv failed: ");
		return -1;
	}
	_buf[recvsize] = '\0';

	_rb->write(_buf, recvsize);
	sendMsg(clifd, "===RECEIVED===\0", 15);

	return recvsize;
}

int Server::mainLoop()
{
	int res = 0;

	while (1) {
		connectNewClient();
		while (1)
		{
			if (_write_flag) {
				res = writePoll();
			} else {
				res = readPoll();
			}
			if (errno == EBADF || res < 0)
				break;

			if (res && FD_ISSET(_clifd, &_fds))
			{
				if (_write_flag) {
					_write_flag = false;
					sendMsg(_clifd, _write_content.c_str(), _write_content.size());
				} else {
					std::cout << "\tstart receiving on: " << _clifd << std::endl;
					if (recvMsg(_clifd))
						std::cout << "MSG: " << _buf << std::endl;
					else
						break;
				}
			}
		}

		closeConnection(_clifd);
		std::cout << "\tConnection Closed." << std::endl;
		std::cout << "\tWaiting for next connection." << std::endl;
	}
	return 0;
}

int Server::setBuffer(RingBuffer *p) {
	_rb = p;
}

/*
int main() {
	Server s(8000);
	std::cout << "\tserver start." << std::endl;
	s.mainLoop();

    return 0;
}
*/
