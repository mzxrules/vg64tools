PROGRAM = En_Bird
FINAL = ovl_En_Bird
ADDRESS = 0x809C1BB0

PARTS = header.o $(PROGRAM).o \
	bfunc-1.o bfunc-2.o bfunc-3.o bfunc-4.o bfunc-5.o bfunc-6.o bfunc-7.o bfunc-8.o bfunc-9.o

CC   = mips-gcc
LD   = mips-ld
NOVL = nOVL

ASFLAGS = -I ../../z_snippets
CFLAGS = -G 0 -Os --std=gnu99 -mtune=vr4300 -I ../../z_snippets
LDFLAGS = -L ../../gnu-toolchain -T z64-ovl.ld --emit-relocs
NOVLFLAGS = -vv -c -A $(ADDRESS) -o $(FINAL).ovl

default: $(PROGRAM).ovl

$(PROGRAM).ovl: $(PROGRAM).elf
	$(NOVL) $(NOVLFLAGS) $(PROGRAM).elf

$(PROGRAM).elf: $(PARTS)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)

clean:
	rm -fv $(PROGRAM).elf $(FINAL).ovl $(PARTS)
