CFLAGS=-ansi -O3 -Wpedantic -Werror

all: hostsblock

hostsblock: hostsblock.c
	$(CC) $(CFLAGS) -o hostsblock hostsblock.c
