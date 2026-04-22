CC = gcc
CFLAGS = -Wall -Wextra

pseudo-shell: main.o string_parser.o command.o
	$(CC) $(CFLAGS) -o pseudo-shell main.o string_parser.o command.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

string_parser.o: string_parser.c
	$(CC) $(CFLAGS) -c string_parser.c

command.o: command.c
	$(CC) $(CFLAGS) -c command.c

clean:
	rm -f pseudo-shell *.o
