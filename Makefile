CFLAGS=-std=c89 -O3 -Wpedantic -Werror

all: hostsblock

hostsblock: hostsblock.c
	$(CC) $(CFLAGS) -o hostsblock hostsblock.c
