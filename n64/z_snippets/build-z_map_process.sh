#!/bin/sh
mips-gcc -Os -c z_map_process.c 
mips-ld -T n64.ld -o z_map_process.elf z_map_process.o
mips-objcopy -O binary z_map_process.elf z_map_process2.bin
/home/zzt32/bl/putbin z_map_process2.bin ZELOOTMA.V64 00B0F5AC
