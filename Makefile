CC := gcc
CFLAGS := -O2 -Wall
INSTALL_DIR := /usr/local/bin

all: g722enc g7221enc

clean:
	rm -f *.o g722enc g7221enc

install: g722enc g7221enc
	install -t $(INSTALL_DIR) $^

g722enc: g722enc.o g722enc.c
	$(CC) $(CFLAGS) -lsndfile -lspandsp -o $@ $^

g7221enc: g7221enc.o g7221enc.c
	$(CC) $(CFLAGS) -lsndfile -lg722_1 -o $@ $^
