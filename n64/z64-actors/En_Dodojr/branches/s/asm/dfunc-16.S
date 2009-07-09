#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f706c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f16
        .ent            En_Dodojr_f16

En_Dodojr_f16:        

        lui     $at,0x4220
        mtc1    $at,$f4
        lwc1    $f6,144(a0)
        li      v0,1
        c.lt.s  $f4,$f6
        nop
        bc1f    $Lf16_01
        nop
        jr      ra
        move    v0,zero
$Lf16_01:
        jr      ra
        nop
        
        .end            En_Dodojr_f16
        .set            at
        .set            reorder

