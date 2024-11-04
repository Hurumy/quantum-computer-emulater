
#include "Qbyte.hpp"

#include <iostream>
#include <iomanip>
#include <complex>

Qbyte::Qbyte();
Qbyte::~Qbyte();

int	Qbyte::setOneBit(Qbit q) {
	if (_bits.size() > 8)
		return -1;
	else
		_bits.push_back(q);
	return 0;
}

int Qbyte::setFromPacket(std::string p) {
	std::complex<double> a;
	std::complex<double> b;
	std::string tmp;

	std::cout << "\tQbyte p: " << p << std::endl;
	if (p.size() < 16)
		return -1;
	_ss << p;
	_ss >> tmp;
	if (tmp != "QBIT")
		return -1;
	_ss >> tmp;
	if (tmp != "a:")
		return -1;
	_ss >> a;
	_ss >> tmp;
	if (tmp != "b:")
		return -1;
	_ss >> b;
	_ss >> tmp;
	if (tmp != "END")
		return -1;
	return 0;
}



