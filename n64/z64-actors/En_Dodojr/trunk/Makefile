PROGRAM = En_Dodojr
FINAL   = ovl_$(PROGRAM)
ADDRESS = 0x809F63C0
TGT_ROM = ZELOOTMA.Z64

HEADER = c/header.o

SRC_ASM	=		\
	asm/data.o	\
	asm/rodata.o	\
        asm/dfunc-01.o	\
        asm/dfunc-02.o	\
        asm/dfunc-03.o	\
        asm/dfunc-04.o	\
        asm/dfunc-05.o	\
        asm/dfunc-06.o	\
        asm/dfunc-07.o	\
        asm/dfunc-08.o	\
        asm/dfunc-09.o	\
        asm/dfunc-10.o	\
        asm/dfunc-11.o	\
        asm/dfunc-12.o	\
        asm/dfunc-13.o	\
        asm/dfunc-14.o	\
        asm/dfunc-15.o	\
        asm/dfunc-16.o	\
        asm/dfunc-17.o	\
        asm/dfunc-18.o	\
        asm/dfunc-19.o	\
        asm/dfunc-20.o	\
        asm/dfunc-21.o	\
        asm/dfunc-22.o	\
        asm/dfunc-23.o	\
        asm/dfunc-24.o	\
        asm/dfunc-25.o	\
        asm/dfunc-26.o	\
        asm/dfunc-27.o	\
        asm/dfunc-28.o	\
        asm/dfunc-29.o	\
        asm/dfunc-30.o	\
        asm/dfunc-31.o	\
        asm/dfunc-32.o	\
        asm/dfunc-33.o	\
        asm/dfunc-34.o	\
        asm/dfunc-35.o	\
        asm/dfunc-36.o	\
        asm/dfunc-37.o	\
        asm/dfunc-38.o	\
        asm/dfunc-39.o

SRC_C =			\
#       c/dfunc-01.o	\
#       c/dfunc-02.o	\
#       c/dfunc-03.o	\
#       c/dfunc-04.o	\
#       c/dfunc-05.o	\
#       c/dfunc-06.o	\
#       c/dfunc-07.o	\
#       c/dfunc-08.o	\
#       c/dfunc-09.o	\
#       c/dfunc-10.o	\
#       c/dfunc-11.o	\
#       c/dfunc-12.o	\
#       c/dfunc-13.o	\
#       c/dfunc-14.o	\
#       c/dfunc-15.o	\
#       c/dfunc-16.o	\
#       c/dfunc-17.o	\
#       c/dfunc-18.o	\
#       c/dfunc-19.o	\
#       c/dfunc-20.o	\
#       c/dfunc-21.o	\
#       c/dfunc-22.o	\
#       c/dfunc-23.o	\
#       c/dfunc-24.o	\
#       c/dfunc-25.o	\
#       c/dfunc-26.o	\
#       c/dfunc-27.o	\
#       c/dfunc-28.o	\
#       c/dfunc-29.o	\
#       c/dfunc-30.o	\
#       c/dfunc-31.o	\
#       c/dfunc-32.o	\
#       c/dfunc-33.o	\
#       c/dfunc-34.o	\
#       c/dfunc-35.o	\
#       c/dfunc-36.o	\
#       c/dfunc-37.o	\
#       c/dfunc-38.o	\
#       c/dfunc-39.o

PARTS = $(HEADER) $(SRC_ASM) $(SRC_C)


CC   = mips-gcc
LD   = mips-ld
NOVL = nOVL

ASFLAGS   = -I ../../../z_snippets
CFLAGS    = -G 0 -Os --std=gnu99 -mtune=vr4300 -I ../../../z_snippets
LDFLAGS   = -L ../../../gnu-toolchain -T z64-ovl.ld --emit-relocs
NOVLFLAGS = -vv -c -A $(ADDRESS) -o $(FINAL).ovl

default: $(PROGRAM).ovl

$(PROGRAM).ovl: $(PROGRAM).elf
	$(NOVL) $(NOVLFLAGS) $(PROGRAM).elf
	nOVLins -a 114 -o 0x03FF0000 $(FINAL).ovl $(TGT_ROM)

$(PROGRAM).elf: $(PARTS)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)

clean:
	rm -fv $(PROGRAM).elf $(FINAL).ovl $(PARTS)
