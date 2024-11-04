
#include "communicater/RingBuffer.hpp"
#include "communicater/Server.hpp"
#include "Qbyte.hpp"

#include <string.h>

#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>
#include <string>

RingBuffer rb;

std::vector<std::string> packets;

void serverThread() {
	Server s(8000);
	s.setBuffer(&rb);
	s.mainLoop();
}

void qbyteParserThread() {
	char tmp[256];
	char*	tmphead;

	tmphead = &tmp[0];

	while (1) {
		if (!rb.canRead()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}

		*tmphead = rb.read(1).c_str()[0];
		tmphead ++;

		if (strncmp(&tmp[0], "QBIT a:", 7) == 0 && strncmp((tmphead-4), " END", 4) == 0) {
			std::string s(tmp, sizeof(tmphead-tmp));
			packets.push_back(s);
			std::cout << "Packet: " << s << std::endl;
			tmphead = &tmp[0];
		}
	}
}


int main() {
	// Fork a Server
	std::thread t1(serverThread);

	// Receiving a msg
	qbyteParserThread();

	return 0;
}


