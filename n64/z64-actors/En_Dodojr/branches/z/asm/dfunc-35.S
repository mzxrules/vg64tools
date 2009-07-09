#include <mips.h>
#include "../dodojr.h"

        .text
        
        /*
        *# Original address: 0x809f7c48
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f35
        .ent            En_Dodojr_f35

En_Dodojr_f35:        

        addiu   sp,sp,-24
        sw      ra,20(sp)
        sw      a1,28(sp)
        lh      v0,512(a0)
        bnez    v0,$Lf35_01
        addiu   t6,v0,-1
        b       $Lf35_02
        move    v1,zero
$Lf35_01:
        sh      t6,512(a0)
        lh      v1,512(a0)
$Lf35_02:
        bnezl   v1,$Lf35_03
        lw      ra,20(sp)
        jal     En_Dodojr_f18
        nop
        lw      ra,20(sp)
$Lf35_03:
        addiu   sp,sp,24
        jr      ra
        nop
        
        .end            En_Dodojr_f35
        .set            at
        .set            reorder
