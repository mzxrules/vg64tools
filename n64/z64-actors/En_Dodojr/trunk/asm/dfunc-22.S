#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f74c4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f22
        .ent            En_Dodojr_f22

En_Dodojr_f22:        

        addiu   sp,sp,-48
        sw      s0,32(sp)
        move    s0,a0
        sw      ra,36(sp)
        sw      a1,52(sp)
        li      t6,100
        sw      t6,16(sp)
        move    a1,zero
        addiu   a0,a0,180
        li      a2,4
        jal     0x8007869c
        li      a3,1000
        lh      t7,180(s0)
        lui     $at,0x4680
        mtc1    $at,$f6
        mtc1    t7,$f4
        lui     $at,0x4270
        mtc1    $at,$f10
        cvt.s.w $f0,$f4
        lwc1    $f8,12(s0)
        move    a0,s0
        li      a2,3
        div.s   $f0,$f0,$f6
        mul.s   $f16,$f10,$f0
        add.s   $f18,$f8,$f16
        swc1    $f18,40(s0)
        swc1    $f0,44(sp)
        jal     En_Dodojr_f4
        lw      a1,52(sp)
        lwc1    $f0,44(sp)
        mtc1    zero,$f4
        lui     t8,0x8003
        addiu   t8,t8,-18964
        c.eq.s  $f0,$f4
        
	.set		at
	#lui     $at,0x809f		# 0x809F7F8C
        #lwc1    $f6,32652($at)		# rodata+28
	lwc1	$f6,(__rodata_start+28)
	.set		noat
	
        bc1fl   $Lf22_01
        lw      ra,36(sp)
        lh      t9,180(s0)
        sw      t8,192(s0)
        sh      t9,48(s0)
	
        #lui     t0,0x809f		# 0x809F758C
        #addiu   t0,t0,30092		# En_Dodojr_f23
	la	t0,En_Dodojr_f23
	
        sw      t0,400(s0)
        swc1    $f6,104(s0)
        lw      ra,36(sp)
$Lf22_01:
        lw      s0,32(sp)
        addiu   sp,sp,48
        jr      ra
        nop
        
        .end            En_Dodojr_f22
        .set            at
        .set            reorder
