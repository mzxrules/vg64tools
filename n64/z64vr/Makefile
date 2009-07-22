# Name
PROGRAM = z64vr
PARTS   = $(PROGRAM).o

# Environment variables
CC      = mips-gcc
LD      = mips-ld
OBJCOPY = mips-objcopy
CHEAT   = /home/spinout/n64/root/bin/nemucheat
BINCODE = /home/spinout/n64/root/bin/bin2code

# Flags
LDFLAGS = -T z64vr.x -L .
CFLAGS  =  -G 0 -O3 --std=gnu99 -mtune=vr4300 -march=vr4300
#CFLAGS  = -fno-builtin -std=gnu99 -nodefaultlibs -march=vr4300 -mtune=vr4300 \
#		  -I../include -I. $(NOBUILTIN) -Os -mno-gpopt

# Compile binary
all: $(PROGRAM).bin
	$(BINCODE) $(PROGRAM).bin 80600000 codes.txt
	cat hook codes.txt | $(CHEAT) "Vowel Replacement" 4 > final.txt

$(PROGRAM).bin: $(PROGRAM).elf
	$(OBJCOPY) $(PROGRAM).elf $(PROGRAM).bin -O binary

$(PROGRAM).elf: $(PARTS)
	$(LD) -o $(PROGRAM).elf	$(PARTS) $(LDFLAGS) 
	
clean:
	rm *.o *.elf *~ *.bin final.txt codes.txt -vf
