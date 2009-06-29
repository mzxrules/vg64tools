############################
# Nintendo 64 Disassembler #
############################

# Project name
NAME = n64dasm

# Program parts
PARTS = opprintf.o decoder.o sym.o swap.o $(NAME).o 

# Environment
CC = gcc

# Standard flags
CFLAGS  += -DVERSION=\"$(shell cat VERSION)\" -D_GNU_SOURCE -std=gnu99 -Wall -O3 -pedantic $(shell pkg-config --cflags glib-2.0)
LDFLAGS +=  $(shell pkg-config --libs glib-2.0)

# Default target
all: $(NAME)

# Build the program
$(NAME): $(PARTS)
	$(CC) -o $(NAME) $(PARTS) $(LDFLAGS)

# Install the program
install: all
	cp -v $(NAME) /usr/bin
	mkdir -p /usr/man/man1
	cp -v $(NAME).1 /usr/man/man1

# Remove installed components
uninstall:
	rm -v /usr/bin/$(NAME)
	rm -v /usr/man/man1/$(NAME).1

clean:
	rm -fv $(NAME) $(PARTS)
