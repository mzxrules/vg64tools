#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f6a20
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f8
        .ent            En_Dodojr_f8

En_Dodojr_f8:        

        addiu   sp,sp,-48
        sw      s0,40(sp)
        move    s0,a0
        sw      ra,44(sp)
        lui     a0,0x600
        jal     0x800a2000
        addiu   a0,a0,1184
        mtc1    v0,$f4
        mtc1    zero,$f0
        lui     $at,0xc120
        cvt.s.w $f6,$f4
        mtc1    $at,$f8
        lui     a1,0x600
        li      t6,2
        mfc1    a3,$f0
        sw      t6,20(sp)
        addiu   a1,a1,1184
        swc1    $f6,16(sp)
        addiu   a0,s0,332
        lui     a2,0x3f80
        jal     0x800a51a0
        swc1    $f8,24(sp)
        mtc1    zero,$f0
        lh      t7,508(s0)
        #lui     $at,0x809f
	lui	$at,%hi(__rodata_start+8)
        swc1    $f0,104(s0)
        swc1    $f0,92(s0)
        swc1    $f0,100(s0)
        #lwc1    $f10,32632($at)
	lwc1	$f10,(%lo(__rodata_start+8))($at)
	
        #.set at
        #lwc1    $f10, (__rodata_start + 8)
        #.set noat
	
        lui     $at,0x4120
        bnez    t7, Lf8_00
        swc1    $f10,108(s0)
        mtc1    $at,$f16
        li      t8,3
        sh      t8,508(s0)
        swc1    $f16,96(s0)
Lf8_00:
        lw      ra,44(sp)
        lw      s0,40(sp)
        addiu   sp,sp,48
        jr      ra
        nop
        
        .end            En_Dodojr_f8
        .set            at
        .set            reorder
