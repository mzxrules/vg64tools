#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f77ac
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f26
        .ent            En_Dodojr_f26

En_Dodojr_f26:        

        addiu   sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        sw      a1,36(sp)
        lbu     t6,276(a0)
        move    s0,a0
        lui     $at,0x4f80
        mtc1    t6,$f4
        bgez    t6,$Lf26_01
        cvt.s.w $f6,$f4
        mtc1    $at,$f8
        nop
        add.s   $f6,$f6,$f8
$Lf26_01:
        lui     $at,0x4100
        mtc1    $at,$f10
	
	.set		at
        #lui     $at,0x809f		# 0x809F7F90
        #lwc1    $f18,32656($at)	#
	lwc1	$f18,(__rodata_start + 32)
	.set		noat
	
        div.s   $f16,$f6,$f10
        move    a0,s0
        mul.s   $f4,$f18,$f16
        jal     0x8002d868
        swc1    $f4,520(s0)
        move    a0,s0
        jal     En_Dodojr_f6
        lw      a1,36(sp)
        beqz    v0,$Lf26_02
        li      t7,60
        sh      t7,514(s0)
        jal     En_Dodojr_f9
        move    a0,s0
        li      t8,7
	
        #lui     t9,0x809f		# 0x809F784C
        #addiu   t9,t9,30796		#
	la	t9,En_Dodojr_f27
	
        sh      t8,508(s0)
        sw      t9,400(s0)
$Lf26_02:
        lw      ra,28(sp)
        lw      s0,24(sp)
        addiu   sp,sp,32
        jr      ra
        nop
        
        .end            En_Dodojr_f26
        .set            at
        .set            reorder

