CC = gcc
CFLAGS = -W -Wall -Wextra -Wpedantic -pedantic -std=c11 -ggdb3

GGCFLAGS = -fanalyzer -Wanalyzer-too-complex

CLANG_FLAGS_MEMSAN = -fsanitize=memory -fno-omit-frame-pointer
CLANG_FLAGS_UNDEFB = -fsanitize=undefined -fno-sanitize-recover=all
CLANG_FLAGS_ADRSAN = -fsanitize=address -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

run: build
	./app

memtest: build
	valgrind --tool=memcheck -s --leak-check=full ./app

pedantic:
	clang ${CLANG_FLAGS_MEMSAN} pq/pq.c app.c -o app
	clang ${CLANG_FLAGS_UNDEFB} pq/pq.c app.c -o app
	clang ${CLANG_FLAGS_ADRSAN} pq/pq.c app.c -o app
	gcc ${CFLAGS} ${GCCFLAGS} pq/pq.c app.c -o app

build:
	${CC} ${CFLAGS} pq/pq.c app.c -o app

clean:
	rm app
	rm vgcore.*