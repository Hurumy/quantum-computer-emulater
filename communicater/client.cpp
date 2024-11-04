
#include "Client.hpp"

#include <iostream>
#include <iomanip>

Client::Client(int port, std::string hostname){
	makeSocket();
	getHostByName(hostname);
	setServInfo(port);
	connect();
}

Client::~Client() {
	close(_sockfd);
}

int Client::makeSocket() {
    _sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
	return 0;
}

int Client::getHostByName(std::string hostname) {
    _serverinfo = gethostbyname(hostname.c_str());
    if (_serverinfo == NULL) {
        perror("no such host");
        exit(-1);
    }
	return 0;
}

int Client::setServInfo(int port) {
    memset((char *)&_serv_addr, 0, sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    memcpy((char *)&_serv_addr.sin_addr.s_addr, (char *)_serverinfo->h_addr,
		  _serverinfo->h_length);
    _serv_addr.sin_port = htons(port);
}

int Client::connect() {
    if (::connect(_sockfd, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
}

int Client::sendMsg(std::string p) {
    int n = send(_sockfd, p.c_str(), p.size(), 0);
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }

	// packet check
    n = recv(_sockfd, &_buf[0], sizeof(_buf), 0);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
	_buf[n] = '\0';
	if (strcmp(_buf, "===RECEIVED===") == 0)
		return 0;
	return n;
}

int Client::recvMsg() {
    int n = recv(_sockfd, &_buf[0], sizeof(_buf), 0);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
	_buf[n] = '\0';
	std::cout << "MSG: " << _buf << std::endl;
}

int main(int argc, char *argv[]) {
	Client c(8000, "localhost");
	c.sendMsg("QBIT a:1 b:0 END\0");
	c.recvMsg();

    return 0;
}

