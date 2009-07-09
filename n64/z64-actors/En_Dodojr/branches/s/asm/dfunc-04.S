#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6510
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f4
        .ent            En_Dodojr_f4

En_Dodojr_f4:        

        addiu   sp,sp,-168
        lui     t6,0x809f
        sw      ra,108(sp)
        sw      s8,104(sp)
        sw      s7,100(sp)
        sw      s6,96(sp)
        sw      s5,92(sp)
        sw      s4,88(sp)
        sw      s3,84(sp)
        sw      s2,80(sp)
        sw      s1,76(sp)
        sw      s0,72(sp)
        sdc1    $f24,64(sp)
        sdc1    $f22,56(sp)
        sdc1    $f20,48(sp)
        addiu   t6,t6,32488 /* 0x7EE8, t6 = 0x809F7EE8 = within .data section */
        lw      t8,0(t6)
        addiu   s5,sp,164
        lui     t9,0x809f
        addiu   t9,t9,32492 /* 0x7EEC, t9 = 0x809F7EEC = within .data section */
        sw      t8,0(s5)
        lw      t1,0(t9)
        addiu   s6,sp,160
        lui     t2,0x809f
        addiu   t2,t2,32496 /* 0x7EF0, t2 = 0x809F7EF0 = within .data section */
        sw      t1,0(s6)
        lw      t4,0(t2)
        addiu   s7,sp,148
        lui     t5,0x809f
        sw      t4,0(s7)
        lw      t3,4(t2)
        addiu   t5,t5,32508 /* 0x7EFC, t5 = 0x809F7EFC = within .data section */
        addiu   s8,sp,136
        sw      t3,4(s7)
        lw      t4,8(t2)
        move    s2,a0
        move    s4,a1
        sw      t4,8(s7)
        lw      t7,0(t5)
        sw      t7,0(s8)
        lw      t6,4(t5)
        sw      t6,4(s8)
        lw      t7,8(t5)
        sw      t7,8(s8)
        jal     0x800fd9ac
        sw      a2,176(sp)
        lui     $at,0x3f00
        mtc1    $at,$f20
        lui     $at,0x4780
        mtc1    $at,$f6
        sub.s   $f4,$f0,$f20
        lw      a2,176(sp)
        lwc1    $f16,500(s2)
        lui     t9,0x1
        mul.s   $f8,$f4,$f6
        move    s1,a2
        swc1    $f16,128(sp)
        trunc.w.s       $f10,$f8
        mfc1    s0,$f10
        nop
        sll     s0,s0,0x10
        bltz    a2, Lf4_03
        sra     s0,s0,0x10
        div     zero,t9,a2
        bnez    a2, Lf4_00
        nop
        break   0x7
Lf4_00:
        li      $at,-1
        bne     a2,$at,Lf4_01
        lui     $at,0x8000
        bne     t9,$at,Lf4_01
        nop
        break   0x6
Lf4_01
        lui     $at,0x41b0
        mtc1    $at,$f24
        lui     $at,0x4080
        mflo    s3
        sll     s3,s3,0x10
        mtc1    $at,$f22
        sra     s3,s3,0x10
Lf4_02:
        jal     0x800fd9ac
        nop
        sub.s   $f18,$f0,$f20
        mul.s   $f4,$f18,$f22
        jal     0x800fd9ac
        swc1    $f4,136(sp)
        sub.s   $f6,$f0,$f20
        sll     a0,s0,0x10
        sra     a0,a0,0x10
        mul.s   $f8,$f6,$f22
        jal     0x80077870
        swc1    $f8,144(sp)
        mul.s   $f10,$f0,$f24
        lwc1    $f16,496(s2)
        sll     a0,s0,0x10
        sra     a0,a0,0x10
        add.s   $f18,$f10,$f16
        jal     0x80077834
        swc1    $f18,124(sp)
        mul.s   $f4,$f0,$f24
        lwc1    $f6,504(s2)
        li      t0,120
        li      t1,40
        li      t2,10
        sw      t2,32(sp)
        sw      t1,28(sp)
        add.s   $f8,$f4,$f6
        sw      t0,24(sp)
        sw      s6,20(sp)
        sw      s5,16(sp)
        swc1    $f8,132(sp)
        move    a0,s4
        addiu   a1,sp,124
        move    a2,s7
        jal     0x8002836c
        move    a3,s8
        addu    s0,s0,s3
        sll     s0,s0,0x10
        addiu   s1,s1,-1
        bgez    s1, Lf4_02
        sra     s0,s0,0x10
Lf4_03:
        lw      ra,108(sp)
        ldc1    $f20,48(sp)
        ldc1    $f22,56(sp)
        ldc1    $f24,64(sp)
        lw      s0,72(sp)
        lw      s1,76(sp)
        lw      s2,80(sp)
        lw      s3,84(sp)
        lw      s4,88(sp)
        lw      s5,92(sp)
        lw      s6,96(sp)
        lw      s7,100(sp)
        lw      s8,104(sp)
        jr      ra
        addiu   sp,sp,168
        .end            En_Dodojr_f4
        .set            at
        .set            reorder

