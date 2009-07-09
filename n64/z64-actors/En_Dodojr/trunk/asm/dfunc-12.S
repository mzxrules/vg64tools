#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6c24
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f12
        .ent            En_Dodojr_f12

En_Dodojr_f12:        

        addiu   sp,sp,-48
        lui     $at,0x4140
        mtc1    $at,$f4
        mtc1    zero,$f6
        sw      s0,40(sp)
        move    s0,a0
        sw      ra,44(sp)
        lui     a1,0x600
        li      t6,2
        sw      t6,20(sp)
        addiu   a1,a1,1828
        addiu   a0,a0,332
        lui     a2,0x3f80
        lui     a3,0x4100
        swc1    $f4,16(sp)
        jal     0x800a51a0
        swc1    $f6,24(sp)
        move    a0,s0
        jal     0x8002f828
        li      a1,14374
        mtc1    zero,$f0
        
	.set		at
        #lui     $at,0x809f		# 0x809F7F88
        #lwc1    $f8,32648($at)		# rodata+24
	lwc1	$f8,(En_Dodojr_rodata+24)
	.set		noat
        
        swc1    $f8,108(s0)
        swc1    $f0,104(s0)
        swc1    $f0,92(s0)
        swc1    $f0,100(s0)
        lw      ra,44(sp)
        lw      s0,40(sp)
        addiu   sp,sp,48
        jr      ra
        nop
        
        .end            En_Dodojr_f12
        .set            at
        .set            reorder
