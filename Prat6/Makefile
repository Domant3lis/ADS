CC = clang
CFLAGS = -W -Wextra -Wall -Wpedantic -pedantic
CFLAGS_MEMSAN = -fsanitize=memory -fno-omit-frame-pointer
CFLAGS_UNDEFB = -fsanitize=undefined -fno-sanitize-recover=all
CFLAGS_ADRSAN = -fsanitize=address -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

excessive_test:
	$(CC) $(CFLAGS_ADRSAN) $(CFLAGS_UNDEFB) -g demo.c sort.c -o demo
	$(CC) $(CFLAGS_MEMSAN) -g demo.c sort.c -o demo
	$(CC) $(CFLAGS) -g demo.c sort.c -o demo
	valgrind --tool=memcheck -s --leak-check=full ./demo random.txt
	python3 ./test.py

run: build
	./demo random.txt

build: demo

demo:
	$(CC) $(CFLAGS) demo.c sort.c -o demo
	
