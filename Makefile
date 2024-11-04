
NAME	= recv
SRCS	= main.cpp \
		  Qbyte.cpp \
		  communicater/Server.cpp \
		  communicater/RingBuffer.cpp 

OBJS	= $(SRCS:.c=.o)
CC		= g++
CFLAG	= 


$(NAME):
	$(CC) $(CFLAG) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	rm $(NAME)

re: clean all

.PHONY: clean re

