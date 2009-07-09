#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f72a4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f20
        .ent            En_Dodojr_f20

En_Dodojr_f20:        

        addiu   sp,sp,-40
        sw      a1,44(sp)
        sw      ra,20(sp)
        addiu   a1,a0,404
        sw      a1,36(sp)
        jal     0x800626dc
        sw      a0,40(sp)
        lw      a3,40(sp)
	
        #lui     t6,0x809f		# 0x809F73AC
        #addiu   t6,t6,29612		# En_Dodojr_f21
	la	t6,En_Dodojr_f21
	
        lw      v0,400(a3)
	
        #lui     t7,0x809f		# 0x809F7BE4
        #addiu   t7,t7,31716		# En_Dodojr_f34
	la	t7,En_Dodojr_f34
	
        beql    t6,v0,Lf20_05
        lw      ra,20(sp)
        beq     t7,v0,Lf20_04
	
        #lui     v1,0x809f		# 0x809F74C4
        #addiu   v1,v1,29892		# En_Dodojr_f22
	la	v1,En_Dodojr_f22
	
        beq     v1,v0,Lf20_00
	
        #lui     t8,0x809f		# 0x809F758C
        #addiu   t8,t8,30092		# En_Dodojr_f23
	la	t8,En_Dodojr_f23
	
        beq     t8,v0,Lf20_00
	
        #lui     t9,0x809f		# 0x809F799C
        #addiu   t9,t9,31132		# En_Dodojr_f30
	la	t9,En_Dodojr_f30
	
        bnel    t9,v0,Lf20_01
        lw      a0,44(sp)
Lf20_00:
        lw      a0,44(sp)
        lui     $at,0x1
        ori     $at,$at,0x1e60
        lw      a2,36(sp)
        sw      v1,28(sp)
        sw      a3,40(sp)
        jal     0x8005d79c
        addu    a1,a0,$at
        lw      a3,40(sp)
        lw      v1,28(sp)
        lw      v0,400(a3)
        lw      a0,44(sp)
Lf20_01:
        lui     $at,0x1
        ori     $at,$at,0x1e60
        beq     v1,v0,Lf20_02
        addu    a1,a0,$at
	
        #lui     t0,0x809f		# 0x809F758C
        #addiu   t0,t0,30092		# En_Dodojr_f23
	la	t0,En_Dodojr_f23
	
        beq     t0,v0,Lf20_02
	
        #lui     t1,0x809f		# 0x809F786C
        #addiu   t1,t1,30828		# En_Dodojr_f28
	la	t1,En_Dodojr_f28
	
        beq     t1,v0,Lf20_02
	
        #lui     t2,0x809f		# 0x809F78EC
        #addiu   t2,t2,30956		# En_Dodojr_f29
	la	t2,En_Dodojr_f29
	
        beq     t2,v0,Lf20_02
	
        #lui     t3,0x809f		# 0x809F799C
        #addiu   t3,t3,31132		# En_Dodojr_f30
	la	t3,En_Dodojr_f30
	
        bne     t3,v0,Lf20_03
        nop
Lf20_02:
        lw      a2,36(sp)
        jal     0x8005d9f4
        sw      a1,24(sp)
        lw      a1,24(sp)
        lw      a0,44(sp)
Lf20_03:
        jal     0x8005dc4c
        lw      a2,36(sp)
Lf20_04:
        lw      ra,20(sp)
Lf20_05:
        addiu   sp,sp,40
        jr      ra
        nop
        
        .end            En_Dodojr_f20
        .set            at
        .set            reorder
