all:
	gcc ./src/tmf.c -o ./tmf -Wall
install:
	cp ./tmf /usr/bin/
