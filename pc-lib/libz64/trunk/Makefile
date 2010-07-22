#############################
# Zelda 64 Function Library #
#############################

PROJECT = z64

# Parts
PIECES = z64.o z64at.o z64nt.o z64fs.o z64ot.o z64st.o z64yaz0.o z64detect.o

# Destination
TARGET = lib$(PROJECT).a

# Preferred applications
AR = ar
CC = gcc

# Compiler settings
CFLAGS  = $(shell pkg-config --cflags glib-2.0 n64rom) -std=gnu99 -I. \
	  -Wall -pedantic -D_GNU_SOURCE -U_FORTIFY_SOURCE
ifeq ($(DBG),1)
	CFLAGS += -g -DDEBUG
else
	CFLAGS += -O3
endif
	
$(TARGET): $(PIECES)
	$(AR) -rcs -o $(TARGET) $(PIECES)

install: $(TARGET)
	mkdir -p /usr/include/z64
	cp -v z64*.h /usr/include/z64/
	cp -v z64.pc /usr/lib/pkgconfig/
	cp -v $(TARGET) /usr/lib

clean:
	rm -fv $(TARGET) $(PIECES)

