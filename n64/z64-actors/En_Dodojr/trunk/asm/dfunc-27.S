#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f784c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f27
        .ent            En_Dodojr_f27

En_Dodojr_f27:        

        addiu   sp,sp,-24
        sw      ra,20(sp)
        jal     0x809f7b3c
        nop
        lw      ra,20(sp)
        addiu   sp,sp,24
        jr      ra
        nop
        
        .end            En_Dodojr_f27
        .set            at
        .set            reorder
