#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f70e8
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f19
        .ent            En_Dodojr_f19

En_Dodojr_f19:        

        addiu   sp,sp,-48
        sw      ra,36(sp)
        sw      s0,32(sp)
        lw      v0,400(a0)
	
        #lui     t6,0x809f		# 0x809F773C
        #addiu   t6,t6,30524		# En_Dodojr_f25
	la	t6,En_Dodojr_f25
	
        move    s0,a0
        beq     t6,v0,Lf19_00
        move    a2,a1
        
        #lui     t7,0x809f		# 0x809F77AC
        #addiu   t7,t7,30636		# En_Dodojr_f26
	la	t7,En_Dodojr_f26
        
        beq     t7,v0,Lf19_00
	
        #lui     t8,0x809f		# 0x809F784C
        #addiu   t8,t8,30796		# En_Dodojr_f27
	la	t8,En_Dodojr_f27
	
        beq     t8,v0,Lf19_00
	
        #lui     t9,0x809f		# 0x809F7A00
        #addiu   t9,t9,31232		# En_Dodojr_f31
	la	t9,En_Dodojr_f31
	
        beq     t9,v0,Lf19_00
	
        #lui     t0,0x809f		# 0x809F7AB8
        #addiu   t0,t0,31416		# En_Dodojr_f32
	la	t0,En_Dodojr_f32
	
        beq     t0,v0,Lf19_00
	
        #lui     t1,0x809f		# 0x809F7B3C
        #addiu   t1,t1,31548		# En_Dodojr_f33
	la	t1,En_Dodojr_f33
	
        beq     t1,v0,Lf19_00
	
        #lui     t2,0x809f		# 0x809F7BE4
        #addiu   t2,t2,31716		# En_Dodojr_f34
	la	t2,En_Dodojr_f34
	
        bnel    t2,v0,Lf19_01
        lbu     t3,7206(a2)
Lf19_00:
        b       Lf19_10
        move    v0,zero
        lbu     t3,7206(a2)
Lf19_01:
        
	#lui     t4,0x809f		# 0x809F73AC
        #addiu   t4,t4,29612		# En_Dodojr_f21
	la	t4,En_Dodojr_f21
	
        beqzl   t3,Lf19_04
        lbu     v1,421(s0)
        beq     t4,v0,Lf19_03
	
        #lui     t5,0x809f		# 0x809F74C4
        #addiu   t5,t5,29892		# En_Dodojr_f22
	la	t5,En_Dodojr_f22
	
        bne     t5,v0,Lf19_02
	
        lui     t6,0x8003
        addiu   t6,t6,-18964
	
        sw      t6,192(s0)
Lf19_02:
        jal     En_Dodojr_f18
        move    a0,s0
Lf19_03:
        b       Lf19_10
        move    v0,zero
        lbu     v1,421(s0)
Lf19_04:

        #lui     t9,0x809f		# 0x809F73AC
        #addiu   t9,t9,29612		# En_Dodojr_f21
	la	t9,En_Dodojr_f21
	
        andi    t7,v1,0x2
        bnez    t7,Lf19_05
        andi    t8,v1,0xfffd
        b       Lf19_10
        move    v0,zero
Lf19_05:
        beq     t9,v0,Lf19_06
        sb      t8,421(s0)
	
        #lui     t0,0x809f		# 0x809F74C4
        #addiu   t0,t0,29892		# En_Dodojr_f22
	la	t0,En_Dodojr_f22
	
        bne     t0,v0,Lf19_07
Lf19_06:

        lui     t1,0x8003
        addiu   t1,t1,-18964
	
        sw      t1,192(s0)
Lf19_07:
        lbu     v0,177(s0)
        li      $at,1
        bnez    v0,Lf19_08
        nop
        lbu     t2,176(s0)
        move    a0,a2
        beqz    t2,Lf19_08
        nop
        jal     0x80032c7c
        move    a1,s0
	
        #lui     t4,0x809f		# 0x809F7C48
        #addiu   t4,t4,31816		# En_Dodojr_f35
	la	t4,En_Dodojr_f35
	
        li      t3,2
        sh      t3,512(s0)
        sw      t4,400(s0)
        b       Lf19_10
        li      v0,1
Lf19_08:
        bnel    v0,$at,Lf19_10
        move    v0,zero
        lw      v0,400(s0)
	
        #lui     t5,0x809f		# 0x809F78EC
        #addiu   t5,t5,30956		# En_Dodojr_f29
	la	t5,En_Dodojr_f29
	
        beq     t5,v0,Lf19_09
	
        #lui     v1,0x809f		# 0x809F786C
        #addiu   v1,v1,30828		# En_Dodojr_f28
	la	v1,En_Dodojr_f28
	
        beq     v1,v0,Lf19_09
        move    a0,s0
        li      a1,14494
        jal     0x8002f828
        sw      v1,40(sp)
        li      t6,120
        sh      t6,510(s0)
        li      t7,120
        sw      t7,16(sp)
        move    a0,s0
        move    a1,zero
        li      a2,200
        jal     0x8003426c
        move    a3,zero
        jal     En_Dodojr_f8
        move    a0,s0
        lw      t8,40(sp)
        sw      t8,400(s0)
Lf19_09:
        move    v0,zero
Lf19_10:
        lw      ra,36(sp)
        lw      s0,32(sp)
        addiu   sp,sp,48
        jr      ra
        nop
        
        .end            En_Dodojr_f19
        .set            at
        .set            reorder
