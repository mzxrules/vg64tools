#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6730
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f5
        .ent            En_Dodojr_f5

En_Dodojr_f5:        

        addiu   sp,sp,-96
        .set at
        #lui     t6,0x809f
        #lui     t7,0x809f
        lw      t6,(En_Dodojr_data + 0x78) /* 0x7F08, t6 = 0x809F7F08 = within .data section */
        lw      t7,(En_Dodojr_data + 0x7C) /* 0x7F0C, t7 = 0x809F7F0C = within .data section */
        .set noat
        #lui     t9,0x809f
        sw      ra,44(sp)
        sw      a0,96(sp)
        sw      a1,100(sp)
        sw      a2,104(sp)
        #addiu   t9,t9,32528 /* 0x7F10, t9 = 0x809F7F10 = within .data section */
        la      t9,(En_Dodojr_data + 0x80)
        sw      t6,92(sp)
        sw      t7,88(sp)
        lw      t1,0(t9)
        addiu   t8,sp,76
        lw      t0,4(t9)
        sw      t1,0(t8)
        lw      t1,8(t9)
        #lui     t3,0x809f
        #addiu   t3,t3,32540 /* 0x7F1C, t3 = 0x809F7F1C = within .data section */
        la      t9,(En_Dodojr_data + 0x8C)
        sw      t0,4(t8)
        sw      t1,8(t8)
        lw      t5,0(t3)
        addiu   t2,sp,64
        lw      t4,4(t3)
        sw      t5,0(t2)
        lw      t5,8(t3)
        sw      t4,4(t2)
        jal     0x800fd9ac
        sw      t5,8(t2)
        lui     $at,0x3f00
        mtc1    $at,$f4
        lui     $at,0x4780
        mtc1    $at,$f8
        sub.s   $f6,$f0,$f4
        lw      t8,96(sp)
        mul.s   $f10,$f6,$f8
        trunc.w.s       $f16,$f10
        mfc1    t7,$f16
        nop
        sh      t7,50(sp)
        lwc1    $f18,128(t8)
        jal     0x800fd9ac
        swc1    $f18,56(sp)
        lui     $at,0x3f00
        mtc1    $at,$f4
        lui     $at,0x4000
        mtc1    $at,$f8
        sub.s   $f6,$f0,$f4
        mul.s   $f10,$f6,$f8
        jal     0x800fd9ac
        swc1    $f10,64(sp)
        lui     $at,0x3f00
        mtc1    $at,$f16
        lui     $at,0x4000
        mtc1    $at,$f4
        sub.s   $f18,$f0,$f16
        lh      a0,50(sp)
        mul.s   $f6,$f18,$f4
        jal     0x80077870
        swc1    $f6,72(sp)
        lui     $at,0x4130
        mtc1    $at,$f8
        lw      t9,104(sp)
        lh      a0,50(sp)
        mul.s   $f10,$f0,$f8
        lwc1    $f16,0(t9)
        add.s   $f18,$f10,$f16
        jal     0x80077834
        swc1    $f18,52(sp)
        lui     $at,0x4130
        mtc1    $at,$f4
        lw      t0,104(sp)
        addiu   t1,sp,92
        mul.s   $f6,$f0,$f4
        lwc1    $f8,8(t0)
        addiu   t2,sp,88
        li      t3,100
        li      t4,60
        li      t5,8
        sw      t5,32(sp)
        add.s   $f10,$f6,$f8
        sw      t4,28(sp)
        sw      t3,24(sp)
        sw      t2,20(sp)
        swc1    $f10,60(sp)
        sw      t1,16(sp)
        lw      a0,100(sp)
        addiu   a1,sp,52
        addiu   a2,sp,76
        jal     0x8002836c
        addiu   a3,sp,64
        lw      ra,44(sp)
        addiu   sp,sp,96
        jr      ra
        nop
        .end            En_Dodojr_f5
        .set            at
        .set            reorder
