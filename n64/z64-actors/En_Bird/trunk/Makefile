PROGRAM = En_Bird
FINAL = ovl_En_Bird
ADDRESS = 0x809C1BB0

PARTS = header.o\
	bfunc-2.o bfunc-4.o bfunc-1.o bfunc-3.o bfunc-5.o bfunc-6.o \
	bfunc-8.o bfunc-9.o bfunc-7.o
	

CC   = mips-gcc
LD   = mips-ld
NOVL = nOVL
NOVLINS = /home/spinout/vg64tools/pc/nOVLins/trunk/nOVLins.py

ASFLAGS = -I /home/spinout/Desktop/n64/z_snippets
CFLAGS = -G 0 -O2 --std=gnu99 -mtune=vr4300 -I /home/spinout/Desktop/n64/z_snippets
LDFLAGS = -L /home/spinout/Desktop/n64/gnu-toolchain -T z64-ovl.ld --emit-relocs
NOVLFLAGS = -vv -c -A $(ADDRESS) -o $(FINAL).ovl

default: $(PROGRAM).ovl

$(PROGRAM).ovl: $(PROGRAM).elf
	$(NOVL) $(NOVLFLAGS) $(PROGRAM).elf
	$(NOVLINS) -a 114 -o 0x03FF0000 ovl_En_Bird.ovl /home/spinout/Desktop/ZD64.z64

$(PROGRAM).elf: $(PARTS)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)

clean:
	rm -fv $(PROGRAM).elf $(FINAL).ovl $(PARTS)
