#include <mips.h>
#include "../dodojr.h"

        .text
        
        /*
        *# Original address: 0x809f7e10
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f39
        .ent            En_Dodojr_f39

En_Dodojr_f39:        

        addiu   sp,sp,-40
        sw      ra,36(sp)
        sw      s0,32(sp)
        sw      a1,44(sp)
        lw      v0,400(a0)
	
        #lui     t6,0x809f		# 0x809F73AC
        #addiu   t6,t6,29612     	# En_Dodojr_f21
	la	t6,En_Dodojr_f21
	
        beq     t6,v0,$Lf39_01
        move    s0,a0
	
        #lui     t7,0x809f		# 0x809F7BE4
        #addiu   t7,t7,31716     	# En_Dodojr_f34
	la	t7,En_Dodojr_f34
	
        beql    t7,v0,$Lf32_21
        lw      ra,36(sp)
        jal     0x80093d18
        lw      a0,0(a1)
	
        #lui     t9,0x809f		# 0x809F7DFC
        #addiu   t9,t9,32252		# En_Dodojr_f38
	la	t9,En_Dodojr_f38
	
        lw      a1,336(s0)
        lw      a2,364(s0)
	
        #lui     a3,0x809f		# 0x809F7D50
        #addiu   a3,a3,32080		# En_Dodojr_f37
	la	a3,En_Dodojr_f37
	
        sw      s0,20(sp)
        sw      t9,16(sp)
        jal     0x800a15c8
        lw      a0,44(sp)
$Lf39_01:
        lw      ra,36(sp)
$Lf32_21:
        lw      s0,32(sp)
        addiu   sp,sp,40
        jr      ra
        nop
        
        .end            En_Dodojr_f39
        .set            at
        .set            reorder
