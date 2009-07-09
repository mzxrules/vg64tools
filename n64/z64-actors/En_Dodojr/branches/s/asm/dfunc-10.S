#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6b38
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f10
        .ent            En_Dodojr_f10

En_Dodojr_f10:        

        addiu   sp,sp,-40
        sw      a0,40(sp)
        sw      ra,36(sp)
        lui     a0,0x600
        jal     0x800a2000
        addiu   a0,a0,1828
        mtc1    v0,$f4
        lui     $at,0xc120
        lw      v1,40(sp)
        cvt.s.w $f6,$f4
        mtc1    $at,$f8
        lui     a1,0x600
        addiu   a1,a1,1828
        lui     a2,0x3f80
        li      a3,0
        swc1    $f6,16(sp)
        sw      zero,20(sp)
        addiu   a0,v1,332
        jal     0x800a51a0
        swc1    $f8,24(sp)
	
	.set		at
        #lui     $at,0x809f		# 0x809F7F80
        #lwc1    $f10,32640($at)	# rodata+16
	lwc1	$f10,(En_Dodojr_rodata+16)
	.set		noat
	
        lw      v1,40(sp)
        lui     $at,0x4120
        mtc1    $at,$f16
        li      t6,3
        sh      t6,508(v1)
        swc1    $f10,108(v1)
        swc1    $f16,96(v1)
        lw      ra,36(sp)
        addiu   sp,sp,40
        jr      ra
        nop
        
        .end            En_Dodojr_f10
        .set            at
        .set            reorder
