PROGRAM = aI

PARTS = aI.o func.o

CC = gcc

CFLAGS  = -O0 -g --std=gnu99 -Wall -pedantic $(shell pkg-config --cflags glib-2.0)
LDFLAGS = $(shell pkg-config --libs glib-2.0)

$(PROGRAM): $(PARTS)
	$(CC) -o $(PROGRAM) $(PARTS) $(LDFLAGS)

clean:
	rm -fv $(PROGRAM) $(PARTS)

