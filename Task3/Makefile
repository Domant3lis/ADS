CFLAGS = -W -Wall -Wextra -Wpedantic -pedantic -std=c2x
GGCFLAGS =  -fanalyzer -Wanalyzer-too-complex

run: build
	./app

debug: build
	valgrind --tool=memcheck -s --leak-check=full ./app

build:
	gcc ${CFLAGS} ${GCCFLAGS} pq/pq.c app.c -o app

clean:
	rm app