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
        jal     En_Dodojr_f5
        addiu   a2,s0,36
        lh      v0,516(s0)
        move    a0,s0
        bnez    v0,$Lf23_01
        addiu   t6,v0,-1
        b       $Lf23_02
        move    v1,zero
$Lf23_01:
        sh      t6,516(s0)
        lh      v1,516(s0)
$Lf23_02:
        bnez    v1,$Lf23_03
        nop
        jal     0x8002f828
        li      a1,14370
        li      t7,5
        sh      t7,516(s0)
$Lf23_03:
        jal     En_Dodojr_f14
        move    a0,s0
        beqz    v0,$Lf23_04
        move    a0,s0
        jal     En_Dodojr_f12
        move    a0,s0
	
        #lui     t8,0x809f		# 0x809F768C
        #addiu   t8,t8,30348		# En_Dodojr_f24
	la	t8,En_Dodojr_f24
	
        b       $Lf23_05
        sw      t8,400(s0)
$Lf23_04:
        jal     En_Dodojr_f15
        lw      a1,36(sp)
        jal     En_Dodojr_f16
        move    a0,s0
        beqz    v0,$Lf23_06
        move    a0,s0
        jal     0x8002f828
        li      a1,14368
        jal     En_Dodojr_f10
        move    a0,s0
	
        #lui     t9,0x809f		# 0x809F799C
        #addiu   t9,t9,31132		# En_Dodojr_f30
	la	t9,En_Dodojr_f30
	
        sw      t9,400(s0)
$Lf23_06:
        lhu     t0,136(s0)
        move    a0,s0
        andi    t1,t0,0x8
        beqzl   t1,$Lf23_07
        lw      ra,28(sp)
        jal     0x8002f828
        li      a1,14371
        jal     En_Dodojr_f11
        move    a0,s0
	
        #lui     t2,0x809f		# 0x809F7A00
        #addiu   t2,t2,31232		# En_Dodojr_f31
	la	t2,En_Dodojr_f31
	
	
        sw      t2,400(s0)
$Lf23_05:
        lw      ra,28(sp)
$Lf23_07:
        lw      s0,24(sp)
        addiu   sp,sp,32
        jr      ra
        nop
        
        .end            En_Dodojr_f23
        .set            at
        .set            reorder
