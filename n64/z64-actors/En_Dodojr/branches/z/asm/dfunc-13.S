#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6ca4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f13
        .ent            En_Dodojr_f13

En_Dodojr_f13:        

        lui     t6,0x809f
        addiu   t6,t6,32552
        lw      t8,0(t6)
        addiu   sp,sp,-48
        addiu   a2,sp,32
        sw      t8,0(a2)
        lw      t7,4(t6)
        move    v1,zero
        sw      t7,4(a2)
        lw      t8,8(t6)
        sw      t8,8(a2)
        lw      v0,7244(a1)
        sw      zero,480(a0)
        li      a1,16
        beqzl   v0,Lf13_07
        move    v0,v1
        lh      t9,28(v0)
Lf13_00:
        bnez    t9, Lf13_01
        nop
        lw      t0,280(v0)
        bnez    t0, Lf13_01
        nop
        lw      t1,304(v0)
        bnezl   t1,Lf13_02
        lh      t2,0(v0)
Lf13_01:
        b       Lf13_06
        lw      v0,292(v0)
        lh      t2,0(v0)
Lf13_02
        beql    a1,t2,Lf13_03
        lwc1    $f4,36(v0)
        b       Lf13_06
        lw      v0,292(v0)
        lwc1    $f4,36(v0)
Lf13_03
        lwc1    $f6,36(a0)
        lwc1    $f0,32(sp)
        lwc1    $f8,40(v0)
        sub.s   $f2,$f4,$f6
        lwc1    $f10,40(a0)
        lwc1    $f4,44(a0)
        abs.s   $f0,$f0
        abs.s   $f16,$f2
        lwc1    $f18,44(v0)
        c.le.s  $f0,$f16
        lwc1    $f0,36(sp)
        sub.s   $f12,$f8,$f10
        bc1t    Lf13_04
        sub.s   $f14,$f18,$f4
        abs.s   $f2,$f12
        abs.s   $f0,$f0
        c.le.s  $f0,$f2
        lwc1    $f0,40(sp)
        bc1t    Lf13_04
        nop
        abs.s   $f2,$f14
        abs.s   $f0,$f0
        c.le.s  $f0,$f2
        nop
        bc1fl   Lf13_05
        sw      v0,480(a0)
Lf13_04:
        b       Lf13_06
        lw      v0,292(v0)
        sw      v0,480(a0)
Lf13_05:
        lw      t4,36(v0)
        li      v1,1
        sw      t4,0(a2)
        lw      t3,40(v0)
        sw      t3,4(a2)
        lw      t4,44(v0)
        sw      t4,8(a2)
        lw      v0,292(v0)
Lf13_06:
        bnezl   v0, Lf13_00
        lh      t9,28(v0)
        move    v0,v1
Lf13_07:
        jr      ra
        addiu   sp,sp,48
        
        .end            En_Dodojr_f13
        .set            at
        .set            reorder
