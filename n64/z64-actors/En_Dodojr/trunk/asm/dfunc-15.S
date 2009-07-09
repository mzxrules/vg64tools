#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6e54
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f15
        .ent            En_Dodojr_f15

En_Dodojr_f15:        

        addiu   sp,sp,-128
        sw      s0,32(sp)
	
        #lui     t7,0x809f		# 0x809F7F34
        #addiu   t7,t7,32564		# .data + 164
	la	t7,(__data_start+164)
	
        move    s0,a0
        sw      ra,36(sp)
        sw      a1,132(sp)
        addiu   t0,t7,48
        addiu   t6,sp,80
Lf15_00:
        lw      t9,0(t7)
        addiu   t7,t7,12
        addiu   t6,t6,12
        sw      t9,-12(t6)
        lw      t8,-8(t7)
        sw      t8,-8(t6)
        lw      t9,-4(t7)
        bne     t7,t0,Lf15_00
        sw      t9,-4(t6)
        lw      v1,480(s0)
        lw      t1,132(sp)
        move    a0,s0
        beqz    v1,Lf15_01
        lw      a2,7236(t1)
        lw      t2,304(v1)
        beqzl   t2,Lf15_02  #Right
        lw      a1,132(sp)
        beqz    v1,Lf15_02_
        nop
        lw      t3,280(v1)
        beqz    t3,Lf15_02_
        nop
Lf15_01:
        lw      a1,132(sp)
Lf15_02:
        jal     En_Dodojr_f13
        sw      a2,72(sp)
        lw      a2,72(sp)
        lw      v1,480(s0)
Lf15_02_:
        beqz    v1,Lf15_03
        addiu   a0,s0,36
        lw      t0,36(v1)
        addiu   t4,sp,60
        sw      t0,0(t4)
        lw      t5,40(v1)
        sw      t5,4(t4)
        lw      t0,44(v1)
        b       Lf15_04
        sw      t0,8(t4)
Lf15_03:
        lw      t8,36(a2)
        addiu   t7,sp,60
        sw      t8,0(t7)
        lw      t6,40(a2)
        sw      t6,4(t7)
        lw      t8,44(a2)
        sw      t8,8(t7)
Lf15_04:
        addiu   a1,sp,60
        jal     0x80077f90
        sw      a0,44(sp)
        lui     $at,0x42a0
        mtc1    $at,$f4
        li      $at,30
        addiu   t5,sp,80
        c.lt.s  $f4,$f0
        nop
        bc1fl   Lf15_07
        lw      a0,44(sp)
        lw      t9,132(sp)
        lwc1    $f6,8(s0)
        lwc1    $f8,12(s0)
        lw      t1,156(t9)
        lwc1    $f16,16(s0)
        add.s   $f10,$f6,$f8
        divu    zero,t1,$at
        mflo    t2
        mtc1    t2,$f4
        add.s   $f18,$f10,$f16
        bgez    t2,Lf15_05
        cvt.s.w $f6,$f4
        lui     $at,0x4f80
        mtc1    $at,$f8
        nop
        add.s   $f6,$f6,$f8
Lf15_05:
        add.s   $f10,$f18,$f6
        li      $at,12
        trunc.w.s       $f16,$f10
        mfc1    v0,$f16
        nop
        sll     v0,v0,0x10
        sra     v0,v0,0x10
        div     zero,v0,$at
        mfhi    v0
        sll     v0,v0,0x10
        sra     v0,v0,0x10
        bgezl   v0,Lf15_06
        sll     t4,v0,0x2
        negu    v0,v0
        sll     v0,v0,0x10
        sra     v0,v0,0x10
        sll     t4,v0,0x2
Lf15_06:
        addu    v1,t4,t5
        lwc1    $f12,0(v1)
        jal     0x80100290
        sw      v1,40(sp)
        lui     $at,0x42a0
        mtc1    $at,$f8
        lwc1    $f4,60(sp)
        lw      v1,40(sp)
        mul.s   $f18,$f8,$f0
        add.s   $f6,$f4,$f18
        swc1    $f6,60(sp)
        jal     0x80104610
        lwc1    $f12,0(v1)
        lui     $at,0x42a0
        mtc1    $at,$f16
        lwc1    $f10,68(sp)
        mul.s   $f8,$f16,$f0
        add.s   $f4,$f10,$f8
        swc1    $f4,68(sp)
        lw      a0,44(sp)
Lf15_07:
        jal     0x80078068
        addiu   a1,sp,60
        sll     a1,v0,0x10
        li      t0,1
        sw      t0,16(sp)
        sra     a1,a1,0x10
        addiu   a0,s0,50
        li      a2,10
        jal     0x8007869c
        li      a3,1000
        lh      t7,50(s0)
        sh      t7,182(s0)
        lw      ra,36(sp)
        lw      s0,32(sp)
        addiu   sp,sp,128
        jr      ra
        nop
        
        .end            En_Dodojr_f15
        .set            at
        .set            reorder
