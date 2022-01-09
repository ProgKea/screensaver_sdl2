CC=gcc
SDL2FLAGS=$(shell pkg-config sdl2 --cflags --libs) -lSDL2_image
CFLAGS=-Wall -pedantic -Werror -Wshadow

sv: main.c
	${CC} ${CFLAGS} -O2 -o $@ $< ${SDL2FLAGS}
