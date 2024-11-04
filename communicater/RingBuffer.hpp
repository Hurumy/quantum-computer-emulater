
#pragma once

#include <string>

#define _BUF_SIZE 8096

class RingBuffer {
	public:
		RingBuffer();
		bool		canRead() const;
		std::string read(size_t siz);
		int			write(char* buf, int siz);
		bool		print() const;
	protected:
		char	_read1bit();
		int		_write1bit(char c);
	private:
		char _buf[_BUF_SIZE+1];
		char *_wp;
		char *_rp;
};

