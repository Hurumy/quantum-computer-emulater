
#include "communicater/RingBuffer.hpp"
#include "communicater/Server.hpp"
#include "Qbyte.hpp"

#include <string.h>

#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>
#include <string>
#include <list>

RingBuffer rb;

std::list<std::string> packets;

void serverThread() {
	Server s(8000);
	s.setBuffer(&rb);
	s.mainLoop();
}

void packetParserThread() {
	char tmp[100];
	char*	tmphead;
	char	c;

	tmphead = tmp;
	memset(tmp, 0, 100);

	while (1) {
		if (!rb.canRead()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}

		// read 1 byte
		c = rb.read(1).c_str()[0];
		if (c == 'Q') {
			tmphead = tmp;
			*tmphead = 'Q';
		} else {
			*tmphead = c;
		}
		tmphead ++;
		*tmphead = '\0';

		if (tmphead - tmp > sizeof(tmp))
			tmphead = &tmp[0];

		// Format check and make a bunch
		if (strncmp(tmp, "QBIT a:", 7) == 0 && strncmp(tmphead-4, " END", 4) == 0) {
			std::string s(tmp, (tmphead-tmp)*sizeof(char));
			packets.push_back(s);
			std::cout << "Packet: " << s << std::endl;
			tmphead = tmp;
		}
	}
}

void	makeQbits() {
	Qbyte qb;
	std::string tmp;

	while (1) {
		// No Packets -> Sleep
		if (packets.size() == 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}

		tmp = packets.front;
		packets.pop_front();
		qb.setFromPacket(tmp);
		qb.out();
	}
}


int main() {
	// Fork a Server
	std::thread t1(serverThread);

	// Receiving a msg
	std::thread t2(packetParserThread);

	// Parsing a msg
	makeQbits();

	return 0;
}


