PROGRAM = nOVL

# nOVL parts
PARTS = main.o mesg.o func.o overlay.o novl.o novl-reloc.o novl-conv.o

# Disassembler
PARTS += decoder.o opprintf.o


CC = gcc
ifeq ($(FINAL), 1)
	CFLAGS = --std=gnu99 -Wall -pedantic -O3 -fomit-frame-pointer $(shell pkg-config --cflags glib-2.0)
else
	CFLAGS = --std=gnu99 -Wall -pedantic -O0 -g $(shell pkg-config --cflags glib-2.0)
endif
LDFLAGS = -lelf $(shell pkg-config --libs glib-2.0)

$(PROGRAM): $(PARTS)
	$(CC) -o $(PROGRAM) $(PARTS) $(LDFLAGS)

clean:
	rm -fv $(PROGRAM) $(PARTS)

