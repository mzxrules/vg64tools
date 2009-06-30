#!/bin/sh
mips-gcc -Os -c z_ovl_apply.c 
mips-ld -T n64.ld -o z_ovl_apply.elf z_ovl_apply.o
mips-objcopy -O binary z_ovl_apply.elf z_ovl_apply2.bin
/home/zzt32/bl/putbin z_ovl_apply2.bin ZELOOTMA.V64 00B73460
