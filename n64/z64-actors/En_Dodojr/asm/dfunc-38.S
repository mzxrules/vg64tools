#include <mips.h>
#include "../dodojr.h"

        .text
        
        /*
        *# Original address: 0x809f7dfc
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f38
        .ent            En_Dodojr_f38

En_Dodojr_f38:        

        sw      a0,0(sp)
        sw      a1,4(sp)
        sw      a2,8(sp)
        jr      ra
        sw      a3,12(sp)
        
        .end            En_Dodojr_f38
        .set            at
        .set            reorder
