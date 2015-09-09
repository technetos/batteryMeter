SRC+=battery.c
CC=gcc
CFLAG+=--std=c99 -fstack-protector-all -fpie -fPIC

battery:
	${CC} ${SRC} ${CFLAG} -o battery

install:
	cp -v battery /usr/bin/

clean:
	rm  battery
