###################
# N64 ROM Library #
###################

PROJECT = n64rom

# Parts
PIECES = n64rom.o n64crc.o swap.o

TARGET = lib$(PROJECT).a


# Preferred applications
CC = gcc
AR = ar

# Compiler settings
CFLAGS  = $(shell pkg-config --cflags glib-2.0) --std=gnu99 -O3 -I. \
	  -Wall -pedantic -U_FORTIFY_SOURCE
	
$(TARGET): $(PIECES)
	$(AR) -rcs -o $(TARGET) $(PIECES)

clean:
	rm -fv $(TARGET) $(PIECES)

install: $(TARGET)
	mkdir -pv /usr/include/n64rom
	cp -v n64rom.h /usr/include/n64rom
	cp -v n64rom.pc /usr/lib/pkgconfig/
	cp -v libn64rom.a /usr/lib/

