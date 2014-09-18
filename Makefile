CC := gcc
CFLAGS := -O2 -Wall
LDFLAGS := -Wl,--no-as-needed
INSTALL_DIR := /usr/local/bin

all: g722enc g7221enc

clean:
	rm -f *.o g722enc g7221enc

install: g722enc g7221enc
	install -t $(INSTALL_DIR) $^

g722enc: g722enc.c
	$(CC) $(CFLAGS) $(LDFLAGS) -lsndfile -lspandsp -o $@ $^

g7221enc: g7221enc.c
	$(CC) $(CFLAGS) $(LDFLAGS) -lsndfile -lg722_1 -o $@ $^
