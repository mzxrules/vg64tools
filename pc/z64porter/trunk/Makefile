PROJECT = z64porter

PARTS = z64porter.o strint.o yaz0.o

CC = gcc

LIBS = glib-2.0 n64rom z64

CFLAGS = $(shell pkg-config --cflags $(LIBS)) -U_FORTIFY_SOURCE -Wall -Werror

LDFLAGS = $(shell pkg-config --libs $(LIBS))

ifeq ($(DBG),1)
	CFLAGS += -g -DDEBUG
else
	CFLAGS += -O3
endif

ifeq ($(WIN32),1) #all this windows stuff is untested
	CFLAGS += -DWIN32
	OUTPUT = $(PROJECT).exe
	RM = del
	CP = copy
	ifeq ($(PREFIX),)
		PREFIX = C:/Program Files
	endif
else
	OUTPUT = $(PROJECT)
	RM = rm
	CP = cp
	ifeq ($(PREFIX),)
		PREFIX = /usr/bin
	endif
endif


all: $(PARTS)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(PARTS) $(LDFLAGS)

install:
	$(CP) -v $(OUTPUT) $(PREFIX)/$(OUTPUT)

uninstall:
	$(RM) -v $(OUTPUT) $(PREFIX)/$(OUTPUT)

clean:
	$(RM) -vf $(PARTS) $(OUTPUT)

