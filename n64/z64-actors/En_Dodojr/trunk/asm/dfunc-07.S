#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6994
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f7
        .ent            En_Dodojr_f7

En_Dodojr_f7:        

        addiu   sp,sp,-40
        sw      a0,40(sp)
        sw      ra,36(sp)
        lui     a0,0x600
        jal     0x800a2000
        addiu   a0,a0,2144
        mtc1    v0,$f4
        lui     $at,0xc120
        lw      v1,40(sp)
        cvt.s.w $f6,$f4
        mtc1    $at,$f8
        lui     a1,0x600
        lui     a2,0x3fe6
        li      t6,1
        sw      t6,20(sp)
        ori     a2,a2,0x6666
        addiu   a1,a1,2144
        swc1    $f6,16(sp)
        li      a3,0
        addiu   a0,v1,332
        jal     0x800a51a0
        swc1    $f8,24(sp)
        lw      v1,40(sp)
        mtc1    zero,$f10
        #lui     $at,0x809f
        swc1    $f10,96(v1)
        #lwc1    $f16,32624($at)
        .set at
        lwc1    $f16, (__rodata_start + 0)
        .set noat
        #lui     $at,0x809f
        swc1    $f16,104(v1)
        #lwc1    $f18,32628($at)
        .set at
        lwc1    $f18, (__rodata_start + 4)
        .set noat
        swc1    $f18,108(v1)
        lw      ra,36(sp)
        addiu   sp,sp,40
        jr      ra
        nop
        
        .end            En_Dodojr_f7
        .set            at
        .set            reorder
