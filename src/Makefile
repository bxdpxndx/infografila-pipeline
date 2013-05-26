CC=g++
CFLAGS=-g --std=c++11 -Wall -Werror

all: renderer line_test

renderer:
	$(CC) $(CFLAGS) -o renderer main.cpp

line_test:
	$(CC) $(CFLAGS) -o line_test line_test.cpp

clean:
	rm -f renderer line_test line_test.tga

