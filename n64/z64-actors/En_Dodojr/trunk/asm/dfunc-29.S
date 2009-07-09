#include <mips.h>
#include "../dodojr.h"

        .text
        
        /*
        *# Original address: 0x809f78ec
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f29
        .ent            En_Dodojr_f29

En_Dodojr_f29:        

        addiu   sp,sp,-24
        sw      ra,20(sp)
        sw      a1,28(sp)
        lh      v0,510(a0)
        bnez    v0,$Lf29_01
        addiu   t6,v0,-1
        b       $Lf29_02
        move    v1,zero
$Lf29_01:
        sh      t6,510(a0)
        lh      v0,510(a0)
        move    v1,v0
$Lf29_02:
        beqz    v1,$Lf29_03
        slti    $at,v0,30
        beqz    $at,$Lf29_04
        andi    t7,v0,0x1
        beqz    t7,$Lf29_05
        lui     $at,0x3fc0
        lui     $at,0x3fc0
        mtc1    $at,$f0
        lwc1    $f4,36(a0)
        lwc1    $f8,44(a0)
        add.s   $f6,$f4,$f0
        add.s   $f10,$f8,$f0
        swc1    $f6,36(a0)
        b       $Lf29_04
        swc1    $f10,44(a0)
$Lf29_05:
        mtc1    $at,$f0
        lwc1    $f16,36(a0)
        lwc1    $f4,44(a0)
        sub.s   $f18,$f16,$f0
        sub.s   $f6,$f4,$f0
        swc1    $f18,36(a0)
        b       $Lf29_04
        swc1    $f6,44(a0)
$Lf29_03:
        jal     En_Dodojr_f7
        sw      a0,24(sp)
        lw      a0,24(sp)
	
        #lui     t8,0x809f		# 0x809F758C
        #addiu   t8,t8,30092		# En_Dodojr_f23
	la	t8,En_Dodojr_f23
	
        sw      t8,400(a0)
$Lf29_04:
        lw      ra,20(sp)
        addiu   sp,sp,24
        jr      ra
        nop
        
        .end            En_Dodojr_f29
        .set            at
        .set            reorder
