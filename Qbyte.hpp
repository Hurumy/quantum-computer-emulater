#pragma once

#include "emulater/Qbit.hpp"

#include <list>
#include <sstream>

class Qbyte {
	public:
		Qbyte();
		~Qbyte();
		int setOneBit(Qbit q);
		int setFromPacket(std::string p);
		int out();
	protected:
	private:
		std::stringstream	_ss;
		std::vector<Qbit> _bits;
};


