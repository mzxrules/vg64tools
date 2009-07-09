#include <mips.h>
#include "../dodojr.h"

        .text
        
        /*
        *# Original address: 0x809f7be4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f34
        .ent            En_Dodojr_f34

En_Dodojr_f34:        

        addiu   sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        sw      a1,36(sp)
        lh      v0,514(a0)
        move    s0,a0
        move    a1,zero
        bnez    v0,$Lf34_01
        addiu   t6,v0,-1
        b       $Lf34_02
        move    v1,zero
$Lf34_01:
        sh      t6,514(s0)
        lh      v1,514(s0)
$Lf34_02:
        bnez    v1,$Lf34_03
        lw      a0,36(sp)
        addiu   a2,s0,36
        jal     0x8001f940
        li      a3,64
        jal     0x8002d570
        move    a0,s0
$Lf34_03:
        lw      ra,28(sp)
        lw      s0,24(sp)
        addiu   sp,sp,32
        jr      ra
        nop
        
        .end            En_Dodojr_f34
        .set            at
        .set            reorder
