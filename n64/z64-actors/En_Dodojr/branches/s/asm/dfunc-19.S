#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f70e8
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f19
        .ent            En_Dodojr_f19

En_Dodojr_f19:        

        addiu   sp,sp,-48
        sw      ra,36(sp)
        sw      s0,32(sp)
        lw      v0,400(a0)
        lui     t6,0x809f
        addiu   t6,t6,30524
        move    s0,a0
        beq     t6,v0,Lf19_00
        move    a2,a1
        lui     t7,0x809f
        addiu   t7,t7,30636
        beq     t7,v0,Lf19_00
        lui     t8,0x809f
        addiu   t8,t8,30796
        beq     t8,v0,Lf19_00
        lui     t9,0x809f
        addiu   t9,t9,31232
        beq     t9,v0,Lf19_00
        lui     t0,0x809f
        addiu   t0,t0,31416
        beq     t0,v0,Lf19_00
        lui     t1,0x809f
        addiu   t1,t1,31548
        beq     t1,v0,Lf19_00
        lui     t2,0x809f
        addiu   t2,t2,31716
        bnel    t2,v0,Lf19_01
        lbu     t3,7206(a2)
Lf19_00:
        b       Lf19_10
        move    v0,zero
        lbu     t3,7206(a2)
Lf19_01:
        lui     t4,0x809f
        addiu   t4,t4,29612
        beqzl   t3,Lf19_04
        lbu     v1,421(s0)
        beq     t4,v0,Lf19_03
        lui     t5,0x809f
        addiu   t5,t5,29892
        bne     t5,v0,Lf19_02
        lui     t6,0x8003
        addiu   t6,t6,-18964
        sw      t6,192(s0)
Lf19_02:
        jal     0x809f709c
        move    a0,s0
Lf19_03:
        b       Lf19_10
        move    v0,zero
        lbu     v1,421(s0)
Lf19_04:
        lui     t9,0x809f
        addiu   t9,t9,29612
        andi    t7,v1,0x2
        bnez    t7,Lf19_05
        andi    t8,v1,0xfffd
        b       Lf19_10
        move    v0,zero
Lf19_05:
        beq     t9,v0,Lf19_06
        sb      t8,421(s0)
        lui     t0,0x809f
        addiu   t0,t0,29892
        bne     t0,v0,Lf19_07
Lf19_06:
        lui     t1,0x8003
        addiu   t1,t1,-18964
        sw      t1,192(s0)
Lf19_07:
        lbu     v0,177(s0)
        li      $at,1
        bnez    v0,Lf19_08
        nop
        lbu     t2,176(s0)
        move    a0,a2
        beqz    t2,Lf19_08
        nop
        jal     0x80032c7c
        move    a1,s0
        lui     t4,0x809f
        li      t3,2
        addiu   t4,t4,31816
        sh      t3,512(s0)
        sw      t4,400(s0)
        b       Lf19_10
        li      v0,1
Lf19_08:
        bnel    v0,$at,Lf19_10
        move    v0,zero
        lw      v0,400(s0)
        lui     t5,0x809f
        addiu   t5,t5,30956
        beq     t5,v0,Lf19_09
        lui     v1,0x809f
        addiu   v1,v1,30828
        beq     v1,v0,Lf19_09
        move    a0,s0
        li      a1,14494
        jal     0x8002f828
        sw      v1,40(sp)
        li      t6,120
        sh      t6,510(s0)
        li      t7,120
        sw      t7,16(sp)
        move    a0,s0
        move    a1,zero
        li      a2,200
        jal     0x8003426c
        move    a3,zero
        jal     0x809f6a20
        move    a0,s0
        lw      t8,40(sp)
        sw      t8,400(s0)
Lf19_09:
        move    v0,zero
Lf19_10:
        lw      ra,36(sp)
        lw      s0,32(sp)
        addiu   sp,sp,48
        jr      ra
        nop
        
        .end            En_Dodojr_f19
        .set            at
        .set            reorder
