CFLAGS ?= -g

all: test-main

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@

test-main: test-main.o heapsort.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	
clean:
	rm -f test-main test-main.o heapsort.o
