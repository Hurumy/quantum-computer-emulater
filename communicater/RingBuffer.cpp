
#include "RingBuffer.hpp"

#include <iostream>
#include <iomanip>
#include <string>

RingBuffer::RingBuffer() {
	_wp = &_buf[0];
	_rp = &_buf[0];
	_buf[_BUF_SIZE] = '\0';
}

bool	RingBuffer::canRead() const {
	if (_wp == _rp)
		return false;
	return true;
}

std::string RingBuffer::read(size_t siz) {
	char c;
	std::string tmp;

	for (size_t i=0; i<siz; i++) {
		c = _read1bit();
		if (c < 0)
			return NULL;
		tmp += c;
	}
	return tmp;
}

int	RingBuffer::write(char *buf, int siz) {
	for (size_t i=0; i<siz; i++) {
		_write1bit(buf[i]);
	}
	return 0;
}


char	RingBuffer::_read1bit() {
	if (_wp == _rp)
		return -1;

	char tmp = *_rp;
	if (_rp - _buf > _BUF_SIZE)
		_rp = &_buf[0];
	else
		_rp = _rp + 1;
	return tmp;
}

int	RingBuffer::_write1bit(char c) {
	*_wp = c;
	if (_wp - _buf > _BUF_SIZE)
		_wp = &_buf[0];
	else
		_wp = _wp + 1;
	return 0;
}

bool	RingBuffer::print() const {
	std::cout << &_buf[0] << std::endl;
	return true;
}

