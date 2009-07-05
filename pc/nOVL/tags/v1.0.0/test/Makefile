PROGRAM = ovl-example

PARTS = $(PROGRAM).o

CC = mips-gcc
AR = mips-ar
LD = mips-ld

ASFLAGS = -march=vr4300 -I.
CFLAGS  = -O1 -std=gnu99 -I. -G0 -march=vr4300 -Wall -pedantic
LDFLAGS = -lc -lnosys -lm


$(PROGRAM).ovl: $(PARTS)
	$(LD) -o $(PROGRAM).elf -T n64.ld --emit-reloc $(PARTS) $(LDFLAGS)
	../nOVL -A 0x80800000 -c -o $(PROGRAM).ovl $(PROGRAM).elf


clean:
	rm -fv *.elf *.o *.ovl

