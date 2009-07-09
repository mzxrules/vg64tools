#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f63c0
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f1
        .ent            En_Dodojr_f1

En_Dodojr_f1:        

        addiu   sp,sp,-64
        sw      s0,40(sp)
        move    s0,a0
        sw      ra,44(sp)
        sw      a1,68(sp)
        li      a1,0
        addiu   a0,a0,180
        move    a2,zero
        jal     0x8002b1e0
        lui     a3,0x4190
        lui     a2,0x600
        lui     a3,0x600
        addiu   t6,s0,524
        addiu   t7,s0,614
        li      t8,15
        sw      t8,24(sp)
        sw      t7,20(sp)
        sw      t6,16(sp)
        addiu   a3,a3,2516
        addiu   a2,a2,8416
        lw      a0,68(sp)
        jal     0x800a457c
        addiu   a1,s0,332
        addiu   a1,s0,404
        sw      a1,52(sp)
        jal     0x8005c364
        lw      a0,68(sp)
        #lui     a3,0x809f
        lw      a1,52(sp)
        #addiu   a3,a3,32432 /* 0x7EBO, A3 = 0x809F7EB0 = within .data section */
        la      a3, (En_Dodojr_data + 0x20)
        lw      a0,68(sp)
        jal     0x8005c4ac
        move    a2,s0
        jal     0x8005b200
        li      a0,4
        #lui     a2,0x809f
        #addiu   a2,a2,32476 /* 0x7EDC, A2 = 0x809F7EDC = within .data section */
        la      a3, (En_Dodojr_data + 0x4C)
        addiu   a0,s0,152
        jal     0x80061efc
        move    a1,v0
        lw      t0,4(s0)
        li      $at,-2
        li      t9,14
        lui     a1,0x3ca3
        and     t1,t0,$at
        sb      t9,279(s0)
        sw      t1,4(s0)
        ori     a1,a1,0xd70a
        jal     0x8002d62c
        move    a0,s0
        #lui     t2,0x809f
        #addiu   t2,t2,29612 /* 0x73AC, t2 = 0x809F73AC = En_Dodojr_f21 */
        la      t2, En_Dodojr_f21
        sw      t2,400(s0)
        lw      ra,44(sp)
        lw      s0,40(sp)
        addiu   sp,sp,64
        jr      ra
        nop
        .end            En_Dodojr_f1
        .set            at
        .set            reorder
