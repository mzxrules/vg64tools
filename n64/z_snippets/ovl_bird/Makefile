PROGRAM = ovl_bird

PARTS = $(PROGRAM).o

CC = mips-gcc
LD = mips-ld

CFLAGS = -G 0 -O3 --std=gnu99 -mtune=vr4300


$(PROGRAM): $(PARTS)
	$(LD) -T n64.ld -o $(PROGRAM).elf $(PARTS)

clean:
	rm -fv $(PROGRAM).elf $(PARTS)
