PROGRAM = nOVL

# nOVL parts
PARTS = main.o mesg.o func.o overlay.o novl.o novl-reloc.o novl-conv.o

# Disassembler
PARTS += decoder.o opprintf.o

PKGS = glib-2.0 libelf

CC = gcc
ifeq ($(FINAL), 1)
	CFLAGS = --std=gnu99 -Wall -pedantic -O3 -fomit-frame-pointer $(shell pkg-config --cflags $(PKGS))
else
	CFLAGS = --std=gnu99 -Wall -pedantic -O0 -g $(shell pkg-config --cflags $(PKGS))
endif
LDFLAGS = $(shell pkg-config --libs $(PKGS))

$(PROGRAM): $(PARTS)
	$(CC) -o $(PROGRAM) $(PARTS) $(LDFLAGS)

clean:
	rm -fv $(PROGRAM) $(PARTS)

