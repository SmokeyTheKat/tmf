PREFIX=~/.local

CSRCS=$(shell find ./src/ -type f -name "*.c")

CC=gcc
CFLAGS=-I./include/ -Ofast -Wall -g

all:
	$(CC) -o ./tmf ${CSRCS} ${CFLAGS}
install:
	cp ./tmf ${PREFIX}/bin/
tc: all
	./tmf