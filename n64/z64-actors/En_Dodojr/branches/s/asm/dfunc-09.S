#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6ac4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f9
        .ent            En_Dodojr_f9

En_Dodojr_f9:        

        addiu   sp,sp,-40
        sw      a0,40(sp)
        sw      ra,36(sp)
        lui     a0,0x600
        jal     0x800a2000
        addiu   a0,a0,1520
        mtc1    v0,$f4
        mtc1    zero,$f0
        lw      a0,40(sp)
        cvt.s.w $f6,$f4
        lui     a1,0x600
        mfc1    a3,$f0
        addiu   a1,a1,1520
        lui     a2,0x3f80
        sw      zero,20(sp)
        swc1    $f6,16(sp)
        addiu   a0,a0,332
        jal     0x800a51a0
        swc1    $f0,24(sp)
        lw      v0,40(sp)
        mtc1    zero,$f8
        lui     $at,0x809f
        swc1    $f8,96(v0)
        lwc1    $f10,32636($at)
        swc1    $f10,108(v0)
        lw      ra,36(sp)
        addiu   sp,sp,40
        jr      ra
        nop
        
        .end            En_Dodojr_f9
        .set            at
        .set            reorder
