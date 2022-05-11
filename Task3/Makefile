CFLAGS = -W -Wall -Wextra -Wpedantic -pedantic -std=c11 -ggdb3
GGCFLAGS =  -fanalyzer -Wanalyzer-too-complex

run: build
	./app

memtest: build
	valgrind --tool=memcheck -s --leak-check=full ./app

build:
	gcc ${CFLAGS} ${GCCFLAGS} pq/pq.c app.c -o app

clean:
	rm app
	rm vgcore.*