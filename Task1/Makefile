CC = clang
CFLAGS = -W -Wextra -Wall -Wpedantic -pedantic
CFLAGS_MEMSAN = -fsanitize=memory -fno-omit-frame-pointer
CFLAGS_UNDEFB = -fsanitize=undefined -fno-sanitize-recover=all
CFLAGS_ADRSAN = -fsanitize=address -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

test:
	clang $(CFLAGS_ADRSAN) $(CFLAGS_UNDEFB) demo.c deque.c -o demo
	clang $(CFLAGS_MEMSAN) demo.c deque.c -o demo
	clang $(CFLAGS) -g demo.c deque.c -o demo
	valgrind --tool=memcheck -s --leak-check=full ./demo
	# ulimit -v 2640; ./demo

release:
	$(CC) demo.c deque.c -O3 -o demo

clean:
	rm demo
	rm -r vgcore.*