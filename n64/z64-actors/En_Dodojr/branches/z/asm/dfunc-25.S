#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f773c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f25
        .ent            En_Dodojr_f25

En_Dodojr_f25:        

        addiu   sp,sp,-24
        sw      ra,20(sp)
        sw      a1,28(sp)
        lh      v0,514(a0)
        bnez    v0,$Lf25_01
        addiu   t6,v0,-1
        b       $Lf25_02
        move    v1,zero
$Lf25_01:
        sh      t6,514(a0)
        lh      v1,514(a0)
$Lf25_02:
        bnezl   v1,$Lf25_03
        lw      ra,20(sp)
        jal     En_Dodojr_f3
        sw      a0,24(sp)
        lw      a0,24(sp)
        li      $at,-2
        lw      t7,4(a0)
        and     t8,t7,$at
        jal     En_Dodojr_f8
        sw      t8,4(a0)
        lw      a0,24(sp)
	
        #lui     t9,0x809f		# 0x809F77AC
        #addiu   t9,t9,30636		# En_Dodojr_f26
	la	t9,En_Dodojr_f26
	
        sw      t9,400(a0)
        lw      ra,20(sp)
$Lf25_03:
        addiu   sp,sp,24
        jr      ra
        nop
        
        .end            En_Dodojr_f25
        .set            at
        .set            reorder
