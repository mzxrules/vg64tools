#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6bbc
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f11
        .ent            En_Dodojr_f11

En_Dodojr_f11:        

        lw      t6,4(a0)
        li      $at,-2
        sw      zero,192(a0)
        and     t7,t6,$at
        sw      t7,4(a0)
        addiu   v0,a0,36
        lw      t9,0(v0)
        mtc1    zero,$f4
        lui     $at,0x809f
        sw      t9,8(a0)
        lw      t8,4(v0)
        li      t0,30
        sw      t8,12(a0)
        lw      t9,8(v0)
        swc1    $f4,104(a0)
        sw      t9,16(a0)
        lwc1    $f6,32644($at)
        sh      t0,514(a0)
        swc1    $f6,108(a0)
        lw      t2,0(v0)
        sw      t2,496(a0)
        lw      t1,4(v0)
        sw      t1,500(a0)
        lw      t2,8(v0)
        jr      ra
        sw      t2,504(a0)
        
        .end            En_Dodojr_f11
        .set            at
        .set            reorder
