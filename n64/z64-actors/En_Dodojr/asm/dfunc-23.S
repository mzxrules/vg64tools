#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f758c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f23
        .ent            En_Dodojr_f23

En_Dodojr_f23:        

        addiu   sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        move    s0,a0
        jal     0x8002d868
        sw      a1,36(sp)
        move    a0,s0
        lw      a1,36(sp)
        jal     0x809f6730
        addiu   a2,s0,36
        lh      v0,516(s0)
        move    a0,s0
        bnez    v0,0x809f75cc
        addiu   t6,v0,-1
        b       0x809f75d4
        move    v1,zero
        sh      t6,516(s0)
        lh      v1,516(s0)
        bnez    v1,0x809f75ec
        nop
        jal     0x8002f828
        li      a1,14370
        li      t7,5
        sh      t7,516(s0)
        jal     0x809f6dd0
        move    a0,s0
        beqz    v0,0x809f7614
        move    a0,s0
        jal     0x809f6c24
        move    a0,s0
        lui     t8,0x809f
        addiu   t8,t8,30348
        b       0x809f7678
        sw      t8,400(s0)
        jal     0x809f6e54
        lw      a1,36(sp)
        jal     0x809f706c
        move    a0,s0
        beqz    v0,0x809f7648
        move    a0,s0
        jal     0x8002f828
        li      a1,14368
        jal     0x809f6b38
        move    a0,s0
        lui     t9,0x809f
        addiu   t9,t9,31132
        sw      t9,400(s0)
        lhu     t0,136(s0)
        move    a0,s0
        andi    t1,t0,0x8
        beqzl   t1,0x809f767c
        lw      ra,28(sp)
        jal     0x8002f828
        li      a1,14371
        jal     0x809f6bbc
        move    a0,s0
        lui     t2,0x809f
        addiu   t2,t2,31232
        sw      t2,400(s0)
        lw      ra,28(sp)
        lw      s0,24(sp)
        addiu   sp,sp,32
        jr      ra
        nop
        
        .end            En_Dodojr_f23
        .set            at
        .set            reorder
