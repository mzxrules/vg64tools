#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6dd0
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f14
        .ent            En_Dodojr_f14

En_Dodojr_f14:        

        addiu   sp,sp,-24
        sw      ra,20(sp)
        lw      v0,480(a0)
        move    a2,a0
        bnezl   v0, Lf14_00
        lw      t6,280(v0)
        b       Lf14_03
        move    v0,zero
        lw      t6,280(v0)
Lf14_00:
        addiu   a0,a2,36
        addiu   a1,v0,36
        beqz    t6, Lf14_01
        nop
        b       Lf14_03
        move    v0,zero
Lf14_01:
        jal     0x80077f90
        sw      a2,24(sp)
        lui     $at,0x41f0
        mtc1    $at,$f4
        lw      a2,24(sp)
        c.lt.s  $f4,$f0
        nop
        bc1fl   Lf14_02
        lw      t7,480(a2)
        b       Lf14_03
        move    v0,zero
        lw      t7,480(a2)
Lf14_02:
        li      v0,1
        sw      a2,280(t7)
Lf14_03:
        lw      ra,20(sp)
        addiu   sp,sp,24
        jr      ra
        nop
        
        .end            En_Dodojr_f14
        .set            at
        .set            reorder
