#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f68b0
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f6
        .ent            En_Dodojr_f6

En_Dodojr_f6:        

        addiu   sp,sp,-24
        sw      ra,20(sp)
        sw      a1,28(sp)
        lwc1    $f4,96(a0)
        mtc1    zero,$f6
        nop
        c.le.s  $f6,$f4
        nop
        bc1fl   Lf6_00
        lh      t6,508(a0)
        b       Lf6_03
        move    v0,zero
        lh      t6,508(a0)
Lf6_00:
        bnezl   t6,Lf6_01
        lhu     t7,136(a0)
        b       Lf6_03
        move    v0,zero
        lhu     t7,136(a0)
Lf6_01:
        li      a1,14459
        andi    t8,t7,0x1
        beqzl   t8,Lf6_03
        move    v0,zero
        jal     0x8002f828
        sw      a0,24(sp)
        lw      a0,24(sp)
        li      a2,10
        lw      t0,36(a0)
        lw      t9,40(a0)
        sw      t0,496(a0)
        lw      t0,44(a0)
        sw      t9,500(a0)
        sw      t0,504(a0)
        jal     En_Dodojr_f4
        lw      a1,28(sp)
        lw      a0,24(sp)
        li      t1,4
        lui     $at,0x4120
        lh      v0,508(a0)
        mtc1    $at,$f8
        subu    t2,t1,v0
        mtc1    t2,$f10
        addiu   t3,v0,-1
        sh      t3,508(a0)
        cvt.s.w $f16,$f10
        lh      t4,508(a0)
        div.s   $f18,$f8,$f16
        bnez    t4,Lf6_02
        swc1    $f18,96(a0)
        mtc1    zero,$f4
        li      v0,1
        b       Lf6_03
        swc1    $f4,96(a0)
Lf6_02:
        move    v0,zero
Lf6_03:
        lw      ra,20(sp)
        addiu   sp,sp,24
        jr      ra
        nop
        .end            En_Dodojr_f6
        .set            at
        .set            reorder
