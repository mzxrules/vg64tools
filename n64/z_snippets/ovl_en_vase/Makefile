PROGRAM = ovl_en_vase

PARTS = $(PROGRAM).o

CC   = mips-gcc
LD   = mips-ld
NOVL = nOVL

CFLAGS = -G 0 -O3 --std=gnu99 -mtune=vr4300
LDFLAGS = -L ../../gnu-toolchain -T z64-ovl.ld --emit-relocs

default: $(PROGRAM).ovl

$(PROGRAM).ovl: $(PARTS)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)
	$(NOVL) -c -A 0x80b28eb0 -o $(PROGRAM).ovl $(PROGRAM).elf

clean:
	rm -fv $(PROGRAM).elf $(PROGRAM).ovl $(PARTS)
