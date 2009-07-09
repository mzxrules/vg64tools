#include <mips.h>

        .text

        /*
        *# Original address: 0x809f63c0
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f1
        .ent            En_Dodojr_f1

En_Dodojr_f1:        

        addiu	sp,sp,-64
        sw	s0,40(sp)
        move	s0,a0
        sw	ra,44(sp)
        sw	a1,68(sp)
        li	a1,0
        addiu	a0,a0,180
        move	a2,zero
        jal	0x8002b1e0
        lui	a3,0x4190
        lui	a2,0x600
        lui	a3,0x600
        addiu	t6,s0,524
        addiu	t7,s0,614
        li	t8,15
        sw	t8,24(sp)
        sw	t7,20(sp)
        sw	t6,16(sp)
        addiu	a3,a3,2516
        addiu	a2,a2,8416
        lw	a0,68(sp)
        jal	0x800a457c
        addiu	a1,s0,332
        addiu	a1,s0,404
        sw	a1,52(sp)
        jal	0x8005c364
        lw	a0,68(sp)
        lui	a3,0x809f
        lw	a1,52(sp)
        addiu	a3,a3,32432 /* 0x7EBO, A3 = 0x809F7EB0 = within .data section */
        lw	a0,68(sp)
        jal	0x8005c4ac
        move	a2,s0
        jal	0x8005b200
        li	a0,4
        lui	a2,0x809f
        addiu	a2,a2,32476 /* 0x7EDC, A2 = 0x809F7EDC = within .data section */
        addiu	a0,s0,152
        jal	0x80061efc
        move	a1,v0
        lw	t0,4(s0)
        li	at,-2
        li	t9,14
        lui	a1,0x3ca3
        and	t1,t0,at
        sb	t9,279(s0)
        sw	t1,4(s0)
        ori	a1,a1,0xd70a
        jal	0x8002d62c
        move	a0,s0
        lui	t2,0x809f
        addiu	t2,t2,29612 /* 0x73AC, t2 = 0x809F73AC = En_Dodojr_f21 */
        sw	t2,400(s0)
        lw	ra,44(sp)
        lw	s0,40(sp)
        addiu	sp,sp,64
        jr	ra
        nop
        .end            En_Dodojr_f1
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f64a8
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f2
        .ent            En_Dodojr_f2

En_Dodojr_f2:        

        addiu	sp,sp,-24
        move	a2,a0
        sw	ra,20(sp)
        move	a0,a1
        jal	0x8005c3ac
        addiu	a1,a2,404
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f2
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f64d0
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f3
        .ent            En_Dodojr_f3

En_Dodojr_f3:        

        addiu	sp,sp,-32
        sw	ra,28(sp)
        sw	a0,32(sp)
        jal	0x8002f828
        li	a1,6158
        li	t6,8
        sw	t6,16(sp)
        lw	a0,32(sp)
        li	a1,16384
        li	a2,200
        jal	0x8003426c
        move	a3,zero
        lw	ra,28(sp)
        addiu	sp,sp,32
        jr	ra
        nop
        .end            En_Dodojr_f3
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6510
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f4
        .ent            En_Dodojr_f4

En_Dodojr_f4:        

        addiu	sp,sp,-168
        lui	t6,0x809f
        sw	ra,108(sp)
        sw	s8,104(sp)
        sw	s7,100(sp)
        sw	s6,96(sp)
        sw	s5,92(sp)
        sw	s4,88(sp)
        sw	s3,84(sp)
        sw	s2,80(sp)
        sw	s1,76(sp)
        sw	s0,72(sp)
        sdc1	$f24,64(sp)
        sdc1	$f22,56(sp)
        sdc1	$f20,48(sp)
        addiu	t6,t6,32488 /* 0x7EE8, t6 = 0x809F7EE8 = within .data section */
        lw	t8,0(t6)
        addiu	s5,sp,164
        lui	t9,0x809f
        addiu	t9,t9,32492 /* 0x7EEC, t9 = 0x809F7EEC = within .data section */
        sw	t8,0(s5)
        lw	t1,0(t9)
        addiu	s6,sp,160
        lui	t2,0x809f
        addiu	t2,t2,32496 /* 0x7EF0, t2 = 0x809F7EF0 = within .data section */
        sw	t1,0(s6)
        lw	t4,0(t2)
        addiu	s7,sp,148
        lui	t5,0x809f
        sw	t4,0(s7)
        lw	t3,4(t2)
        addiu	t5,t5,32508 /* 0x7EFC, t5 = 0x809F7EFC = within .data section */
        addiu	s8,sp,136
        sw	t3,4(s7)
        lw	t4,8(t2)
        move	s2,a0
        move	s4,a1
        sw	t4,8(s7)
        lw	t7,0(t5)
        sw	t7,0(s8)
        lw	t6,4(t5)
        sw	t6,4(s8)
        lw	t7,8(t5)
        sw	t7,8(s8)
        jal	0x800fd9ac
        sw	a2,176(sp)
        lui	at,0x3f00
        mtc1	at,$f20
        lui	at,0x4780
        mtc1	at,$f6
        sub.s	$f4,$f0,$f20
        lw	a2,176(sp)
        lwc1	$f16,500(s2)
        lui	t9,0x1
        mul.s	$f8,$f4,$f6
        move	s1,a2
        swc1	$f16,128(sp)
        trunc.w.s	$f10,$f8
        mfc1	s0,$f10
        nop
        sll	s0,s0,0x10
        bltz	a2, Lf4_03
        sra	s0,s0,0x10
        div	zero,t9,a2
        bnez	a2, Lf4_00
        nop
        break	0x7
Lf4_00:
        li	at,-1
        bne	a2,at,Lf4_01
        lui	at,0x8000
        bne	t9,at,Lf4_01
        nop
        break	0x6
Lf4_01
        lui	at,0x41b0
        mtc1	at,$f24
        lui	at,0x4080
        mflo	s3
        sll	s3,s3,0x10
        mtc1	at,$f22
        sra	s3,s3,0x10
Lf4_02:
        jal	0x800fd9ac
        nop
        sub.s	$f18,$f0,$f20
        mul.s	$f4,$f18,$f22
        jal	0x800fd9ac
        swc1	$f4,136(sp)
        sub.s	$f6,$f0,$f20
        sll	a0,s0,0x10
        sra	a0,a0,0x10
        mul.s	$f8,$f6,$f22
        jal	0x80077870
        swc1	$f8,144(sp)
        mul.s	$f10,$f0,$f24
        lwc1	$f16,496(s2)
        sll	a0,s0,0x10
        sra	a0,a0,0x10
        add.s	$f18,$f10,$f16
        jal	0x80077834
        swc1	$f18,124(sp)
        mul.s	$f4,$f0,$f24
        lwc1	$f6,504(s2)
        li	t0,120
        li	t1,40
        li	t2,10
        sw	t2,32(sp)
        sw	t1,28(sp)
        add.s	$f8,$f4,$f6
        sw	t0,24(sp)
        sw	s6,20(sp)
        sw	s5,16(sp)
        swc1	$f8,132(sp)
        move	a0,s4
        addiu	a1,sp,124
        move	a2,s7
        jal	0x8002836c
        move	a3,s8
        addu	s0,s0,s3
        sll	s0,s0,0x10
        addiu	s1,s1,-1
        bgez	s1, Lf4_02
        sra	s0,s0,0x10
Lf4_03:
        lw	ra,108(sp)
        ldc1	$f20,48(sp)
        ldc1	$f22,56(sp)
        ldc1	$f24,64(sp)
        lw	s0,72(sp)
        lw	s1,76(sp)
        lw	s2,80(sp)
        lw	s3,84(sp)
        lw	s4,88(sp)
        lw	s5,92(sp)
        lw	s6,96(sp)
        lw	s7,100(sp)
        lw	s8,104(sp)
        jr	ra
        addiu	sp,sp,168
        .end            En_Dodojr_f4
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6730
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f5
        .ent            En_Dodojr_f5

En_Dodojr_f5:        

        addiu	sp,sp,-96
        lui	t6,0x809f
        lui	t7,0x809f
        lw	t6,32520(t6) /* 0x7F08, t6 = 0x809F7F08 = within .data section */
        lw	t7,32524(t7) /* 0x7F0C, t7 = 0x809F7F0C = within .data section */
        lui	t9,0x809f
        sw	ra,44(sp)
        sw	a0,96(sp)
        sw	a1,100(sp)
        sw	a2,104(sp)
        addiu	t9,t9,32528 /* 0x7F10, t9 = 0x809F7F10 = within .data section */
        sw	t6,92(sp)
        sw	t7,88(sp)
        lw	t1,0(t9)
        addiu	t8,sp,76
        lw	t0,4(t9)
        sw	t1,0(t8)
        lw	t1,8(t9)
        lui	t3,0x809f
        addiu	t3,t3,32540 /* 0x7F1C, t3 = 0x809F7F1C = within .data section */
        sw	t0,4(t8)
        sw	t1,8(t8)
        lw	t5,0(t3)
        addiu	t2,sp,64
        lw	t4,4(t3)
        sw	t5,0(t2)
        lw	t5,8(t3)
        sw	t4,4(t2)
        jal	0x800fd9ac
        sw	t5,8(t2)
        lui	at,0x3f00
        mtc1	at,$f4
        lui	at,0x4780
        mtc1	at,$f8
        sub.s	$f6,$f0,$f4
        lw	t8,96(sp)
        mul.s	$f10,$f6,$f8
        trunc.w.s	$f16,$f10
        mfc1	t7,$f16
        nop
        sh	t7,50(sp)
        lwc1	$f18,128(t8)
        jal	0x800fd9ac
        swc1	$f18,56(sp)
        lui	at,0x3f00
        mtc1	at,$f4
        lui	at,0x4000
        mtc1	at,$f8
        sub.s	$f6,$f0,$f4
        mul.s	$f10,$f6,$f8
        jal	0x800fd9ac
        swc1	$f10,64(sp)
        lui	at,0x3f00
        mtc1	at,$f16
        lui	at,0x4000
        mtc1	at,$f4
        sub.s	$f18,$f0,$f16
        lh	a0,50(sp)
        mul.s	$f6,$f18,$f4
        jal	0x80077870
        swc1	$f6,72(sp)
        lui	at,0x4130
        mtc1	at,$f8
        lw	t9,104(sp)
        lh	a0,50(sp)
        mul.s	$f10,$f0,$f8
        lwc1	$f16,0(t9)
        add.s	$f18,$f10,$f16
        jal	0x80077834
        swc1	$f18,52(sp)
        lui	at,0x4130
        mtc1	at,$f4
        lw	t0,104(sp)
        addiu	t1,sp,92
        mul.s	$f6,$f0,$f4
        lwc1	$f8,8(t0)
        addiu	t2,sp,88
        li	t3,100
        li	t4,60
        li	t5,8
        sw	t5,32(sp)
        add.s	$f10,$f6,$f8
        sw	t4,28(sp)
        sw	t3,24(sp)
        sw	t2,20(sp)
        swc1	$f10,60(sp)
        sw	t1,16(sp)
        lw	a0,100(sp)
        addiu	a1,sp,52
        addiu	a2,sp,76
        jal	0x8002836c
        addiu	a3,sp,64
        lw	ra,44(sp)
        addiu	sp,sp,96
        jr	ra
        nop
        .end            En_Dodojr_f5
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f68b0
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f6
        .ent            En_Dodojr_f6

En_Dodojr_f6:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        sw	a1,28(sp)
        lwc1	$f4,96(a0)
        mtc1	zero,$f6
        nop
        c.le.s	$f6,$f4
        nop
        bc1fl	Lf6_00
        lh	t6,508(a0)
        b	Lf6_03
        move	v0,zero
        lh	t6,508(a0)
Lf6_00:
        bnezl	t6,Lf6_01
        lhu	t7,136(a0)
        b	0x809f6984
        move	v0,zero
        lhu	t7,136(a0)
Lf6_01:
        li	a1,14459
        andi	t8,t7,0x1
        beqzl	t8,Lf6_03
        move	v0,zero
        jal	0x8002f828
        sw	a0,24(sp)
        lw	a0,24(sp)
        li	a2,10
        lw	t0,36(a0)
        lw	t9,40(a0)
        sw	t0,496(a0)
        lw	t0,44(a0)
        sw	t9,500(a0)
        sw	t0,504(a0)
        jal	0x809f6510
        lw	a1,28(sp)
        lw	a0,24(sp)
        li	t1,4
        lui	at,0x4120
        lh	v0,508(a0)
        mtc1	at,$f8
        subu	t2,t1,v0
        mtc1	t2,$f10
        addiu	t3,v0,-1
        sh	t3,508(a0)
        cvt.s.w	$f16,$f10
        lh	t4,508(a0)
        div.s	$f18,$f8,$f16
        bnez	t4,Lf6_02
        swc1	$f18,96(a0)
        mtc1	zero,$f4
        li	v0,1
        b	Lf6_03
        swc1	$f4,96(a0)
Lf6_02:
        move	v0,zero
Lf6_03:
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f6
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6994
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f7
        .ent            En_Dodojr_f7

En_Dodojr_f7:        

        addiu	sp,sp,-40
        sw	a0,40(sp)
        sw	ra,36(sp)
        lui	a0,0x600
        jal	0x800a2000
        addiu	a0,a0,2144
        mtc1	v0,$f4
        lui	at,0xc120
        lw	v1,40(sp)
        cvt.s.w	$f6,$f4
        mtc1	at,$f8
        lui	a1,0x600
        lui	a2,0x3fe6
        li	t6,1
        sw	t6,20(sp)
        ori	a2,a2,0x6666
        addiu	a1,a1,2144
        swc1	$f6,16(sp)
        li	a3,0
        addiu	a0,v1,332
        jal	0x800a51a0
        swc1	$f8,24(sp)
        lw	v1,40(sp)
        mtc1	zero,$f10
        lui	at,0x809f
        swc1	$f10,96(v1)
        lwc1	$f16,32624(at)
        lui	at,0x809f
        swc1	$f16,104(v1)
        lwc1	$f18,32628(at)
        swc1	$f18,108(v1)
        lw	ra,36(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        .end            En_Dodojr_f7
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6a20
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f8
        .ent            En_Dodojr_f8

En_Dodojr_f8:        

        addiu	sp,sp,-48
        sw	s0,40(sp)
        move	s0,a0
        sw	ra,44(sp)
        lui	a0,0x600
        jal	0x800a2000
        addiu	a0,a0,1184
        mtc1	v0,$f4
        mtc1	zero,$f0
        lui	at,0xc120
        cvt.s.w	$f6,$f4
        mtc1	at,$f8
        lui	a1,0x600
        li	t6,2
        mfc1	a3,$f0
        sw	t6,20(sp)
        addiu	a1,a1,1184
        swc1	$f6,16(sp)
        addiu	a0,s0,332
        lui	a2,0x3f80
        jal	0x800a51a0
        swc1	$f8,24(sp)
        mtc1	zero,$f0
        lh	t7,508(s0)
        lui	at,0x809f
        swc1	$f0,104(s0)
        swc1	$f0,92(s0)
        swc1	$f0,100(s0)
        lwc1	$f10,32632(at)
        lui	at,0x4120
        bnez	t7,Lf8_00
        swc1	$f10,108(s0)
        mtc1	at,$f16
        li	t8,3
        sh	t8,508(s0)
        swc1	$f16,96(s0)
Lf8_00:
        lw	ra,44(sp)
        lw	s0,40(sp)
        addiu	sp,sp,48
        jr	ra
        nop
        .end            En_Dodojr_f8
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6ac4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f9
        .ent            En_Dodojr_f9

En_Dodojr_f9:        

        addiu	sp,sp,-40
        sw	a0,40(sp)
        sw	ra,36(sp)
        lui	a0,0x600
        jal	0x800a2000
        addiu	a0,a0,1520
        mtc1	v0,$f4
        mtc1	zero,$f0
        lw	a0,40(sp)
        cvt.s.w	$f6,$f4
        lui	a1,0x600
        mfc1	a3,$f0
        addiu	a1,a1,1520
        lui	a2,0x3f80
        sw	zero,20(sp)
        swc1	$f6,16(sp)
        addiu	a0,a0,332
        jal	0x800a51a0
        swc1	$f0,24(sp)
        lw	v0,40(sp)
        mtc1	zero,$f8
        lui	at,0x809f
        swc1	$f8,96(v0)
        lwc1	$f10,32636(at)
        swc1	$f10,108(v0)
        lw	ra,36(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        .end            En_Dodojr_f9
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6b38
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f10
        .ent            En_Dodojr_f10

En_Dodojr_f10:        

        addiu	sp,sp,-40
        sw	a0,40(sp)
        sw	ra,36(sp)
        lui	a0,0x600
        jal	0x800a2000
        addiu	a0,a0,1828
        mtc1	v0,$f4
        lui	at,0xc120
        lw	v1,40(sp)
        cvt.s.w	$f6,$f4
        mtc1	at,$f8
        lui	a1,0x600
        addiu	a1,a1,1828
        lui	a2,0x3f80
        li	a3,0
        swc1	$f6,16(sp)
        sw	zero,20(sp)
        addiu	a0,v1,332
        jal	0x800a51a0
        swc1	$f8,24(sp)
        lui	at,0x809f
        lw	v1,40(sp)
        lwc1	$f10,32640(at)
        lui	at,0x4120
        mtc1	at,$f16
        li	t6,3
        sh	t6,508(v1)
        swc1	$f10,108(v1)
        swc1	$f16,96(v1)
        lw	ra,36(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        .end            En_Dodojr_f10
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6bbc
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f11
        .ent            En_Dodojr_f11

En_Dodojr_f11:        

        lw	t6,4(a0)
        li	at,-2
        sw	zero,192(a0)
        and	t7,t6,at
        sw	t7,4(a0)
        addiu	v0,a0,36
        lw	t9,0(v0)
        mtc1	zero,$f4
        lui	at,0x809f
        sw	t9,8(a0)
        lw	t8,4(v0)
        li	t0,30
        sw	t8,12(a0)
        lw	t9,8(v0)
        swc1	$f4,104(a0)
        sw	t9,16(a0)
        lwc1	$f6,32644(at)
        sh	t0,514(a0)
        swc1	$f6,108(a0)
        lw	t2,0(v0)
        sw	t2,496(a0)
        lw	t1,4(v0)
        sw	t1,500(a0)
        lw	t2,8(v0)
        jr	ra
        sw	t2,504(a0)
        .end            En_Dodojr_f11
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6c24
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f12
        .ent            En_Dodojr_f12

En_Dodojr_f12:        

        addiu	sp,sp,-48
        lui	at,0x4140
        mtc1	at,$f4
        mtc1	zero,$f6
        sw	s0,40(sp)
        move	s0,a0
        sw	ra,44(sp)
        lui	a1,0x600
        li	t6,2
        sw	t6,20(sp)
        addiu	a1,a1,1828
        addiu	a0,a0,332
        lui	a2,0x3f80
        lui	a3,0x4100
        swc1	$f4,16(sp)
        jal	0x800a51a0
        swc1	$f6,24(sp)
        move	a0,s0
        jal	0x8002f828
        li	a1,14374
        mtc1	zero,$f0
        lui	at,0x809f
        swc1	$f0,104(s0)
        swc1	$f0,92(s0)
        swc1	$f0,100(s0)
        lwc1	$f8,32648(at)
        swc1	$f8,108(s0)
        lw	ra,44(sp)
        lw	s0,40(sp)
        addiu	sp,sp,48
        jr	ra
        nop
        .end            En_Dodojr_f12
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6ca4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f13
        .ent            En_Dodojr_f13

En_Dodojr_f13:        

        lui	t6,0x809f
        addiu	t6,t6,32552
        lw	t8,0(t6)
        addiu	sp,sp,-48
        addiu	a2,sp,32
        sw	t8,0(a2)
        lw	t7,4(t6)
        move	v1,zero
        sw	t7,4(a2)
        lw	t8,8(t6)
        sw	t8,8(a2)
        lw	v0,7244(a1)
        sw	zero,480(a0)
        li	a1,16
        beqzl	v0,Lf13_07
        move	v0,v1
        lh	t9,28(v0)
Lf13_00:
        bnez	t9, Lf13_01
        nop
        lw	t0,280(v0)
        bnez	t0, Lf13_01
        nop
        lw	t1,304(v0)
        bnezl	t1,Lf13_02
        lh	t2,0(v0)
Lf13_01:
        b	Lf13_06
        lw	v0,292(v0)
        lh	t2,0(v0)
Lf13_02
        beql	a1,t2,Lf13_03
        lwc1	$f4,36(v0)
        b	Lf13_06
        lw	v0,292(v0)
        lwc1	$f4,36(v0)
Lf13_03
        lwc1	$f6,36(a0)
        lwc1	$f0,32(sp)
        lwc1	$f8,40(v0)
        sub.s	$f2,$f4,$f6
        lwc1	$f10,40(a0)
        lwc1	$f4,44(a0)
        abs.s	$f0,$f0
        abs.s	$f16,$f2
        lwc1	$f18,44(v0)
        c.le.s	$f0,$f16
        lwc1	$f0,36(sp)
        sub.s	$f12,$f8,$f10
        bc1t	Lf13_04
        sub.s	$f14,$f18,$f4
        abs.s	$f2,$f12
        abs.s	$f0,$f0
        c.le.s	$f0,$f2
        lwc1	$f0,40(sp)
        bc1t	Lf13_04
        nop
        abs.s	$f2,$f14
        abs.s	$f0,$f0
        c.le.s	$f0,$f2
        nop
        bc1fl	Lf13_05
        sw	v0,480(a0)
Lf13_04:
        b	Lf13_06
        lw	v0,292(v0)
        sw	v0,480(a0)
Lf13_05:
        lw	t4,36(v0)
        li	v1,1
        sw	t4,0(a2)
        lw	t3,40(v0)
        sw	t3,4(a2)
        lw	t4,44(v0)
        sw	t4,8(a2)
        lw	v0,292(v0)
Lf13_06:
        bnezl	v0, Lf13_00
        lh	t9,28(v0)
        move	v0,v1
Lf13_07:
        jr	ra
        addiu	sp,sp,48
        .end            En_Dodojr_f13
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6dd0
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f14
        .ent            En_Dodojr_f14

En_Dodojr_f14:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        lw	v0,480(a0)
        move	a2,a0
        bnezl	v0,0x809f6df4
        lw	t6,280(v0)
        b	0x809f6e44
        move	v0,zero
        lw	t6,280(v0)
        addiu	a0,a2,36
        addiu	a1,v0,36
        beqz	t6,0x809f6e0c
        nop
        b	0x809f6e44
        move	v0,zero
        jal	0x80077f90
        sw	a2,24(sp)
        lui	at,0x41f0
        mtc1	at,$f4
        lw	a2,24(sp)
        c.lt.s	$f4,$f0
        nop
        bc1fl	0x809f6e3c
        lw	t7,480(a2)
        b	0x809f6e44
        move	v0,zero
        lw	t7,480(a2)
        li	v0,1
        sw	a2,280(t7)
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f14
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f6e54
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f15
        .ent            En_Dodojr_f15

En_Dodojr_f15:        

        addiu	sp,sp,-128
        lui	t7,0x809f
        sw	s0,32(sp)
        addiu	t7,t7,32564
        move	s0,a0
        sw	ra,36(sp)
        sw	a1,132(sp)
        addiu	t0,t7,48
        addiu	t6,sp,80
        lw	t9,0(t7)
        addiu	t7,t7,12
        addiu	t6,t6,12
        sw	t9,-12(t6)
        lw	t8,-8(t7)
        sw	t8,-8(t6)
        lw	t9,-4(t7)
        bne	t7,t0,0x809f6e78
        sw	t9,-4(t6)
        lw	v1,480(s0)
        lw	t1,132(sp)
        move	a0,s0
        beqz	v1,0x809f6ed0
        lw	a2,7236(t1)
        lw	t2,304(v1)
        beqzl	t2,0x809f6ed4
        lw	a1,132(sp)
        beqz	v1,0x809f6ee4
        nop
        lw	t3,280(v1)
        beqz	t3,0x809f6ee4
        nop
        lw	a1,132(sp)
        jal	0x809f6ca4
        sw	a2,72(sp)
        lw	a2,72(sp)
        lw	v1,480(s0)
        beqz	v1,0x809f6f0c
        addiu	a0,s0,36
        lw	t0,36(v1)
        addiu	t4,sp,60
        sw	t0,0(t4)
        lw	t5,40(v1)
        sw	t5,4(t4)
        lw	t0,44(v1)
        b	0x809f6f28
        sw	t0,8(t4)
        lw	t8,36(a2)
        addiu	t7,sp,60
        sw	t8,0(t7)
        lw	t6,40(a2)
        sw	t6,4(t7)
        lw	t8,44(a2)
        sw	t8,8(t7)
        addiu	a1,sp,60
        jal	0x80077f90
        sw	a0,44(sp)
        lui	at,0x42a0
        mtc1	at,$f4
        li	at,30
        addiu	t5,sp,80
        c.lt.s	$f4,$f0
        nop
        bc1fl	0x809f7028
        lw	a0,44(sp)
        lw	t9,132(sp)
        lwc1	$f6,8(s0)
        lwc1	$f8,12(s0)
        lw	t1,156(t9)
        lwc1	$f16,16(s0)
        add.s	$f10,$f6,$f8
        divu	zero,t1,at
        mflo	t2
        mtc1	t2,$f4
        add.s	$f18,$f10,$f16
        bgez	t2,0x809f6f94
        cvt.s.w	$f6,$f4
        lui	at,0x4f80
        mtc1	at,$f8
        nop
        add.s	$f6,$f6,$f8
        add.s	$f10,$f18,$f6
        li	at,12
        trunc.w.s	$f16,$f10
        mfc1	v0,$f16
        nop
        sll	v0,v0,0x10
        sra	v0,v0,0x10
        div	zero,v0,at
        mfhi	v0
        sll	v0,v0,0x10
        sra	v0,v0,0x10
        bgezl	v0,0x809f6fd8
        sll	t4,v0,0x2
        negu	v0,v0
        sll	v0,v0,0x10
        sra	v0,v0,0x10
        sll	t4,v0,0x2
        addu	v1,t4,t5
        lwc1	$f12,0(v1)
        jal	0x80100290
        sw	v1,40(sp)
        lui	at,0x42a0
        mtc1	at,$f8
        lwc1	$f4,60(sp)
        lw	v1,40(sp)
        mul.s	$f18,$f8,$f0
        add.s	$f6,$f4,$f18
        swc1	$f6,60(sp)
        jal	0x80104610
        lwc1	$f12,0(v1)
        lui	at,0x42a0
        mtc1	at,$f16
        lwc1	$f10,68(sp)
        mul.s	$f8,$f16,$f0
        add.s	$f4,$f10,$f8
        swc1	$f4,68(sp)
        lw	a0,44(sp)
        jal	0x80078068
        addiu	a1,sp,60
        sll	a1,v0,0x10
        li	t0,1
        sw	t0,16(sp)
        sra	a1,a1,0x10
        addiu	a0,s0,50
        li	a2,10
        jal	0x8007869c
        li	a3,1000
        lh	t7,50(s0)
        sh	t7,182(s0)
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,128
        jr	ra
        nop
        .end            En_Dodojr_f15
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f706c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f16
        .ent            En_Dodojr_f16

En_Dodojr_f16:        

        lui	at,0x4220
        mtc1	at,$f4
        lwc1	$f6,144(a0)
        li	v0,1
        c.lt.s	$f4,$f6
        nop
        bc1f	0x809f7094
        nop
        jr	ra
        move	v0,zero
        .end            En_Dodojr_f16
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7094
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f17
        .ent            En_Dodojr_f17

En_Dodojr_f17:        

        jr	ra
        nop
        .end            En_Dodojr_f17
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f709c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f18
        .ent            En_Dodojr_f18

En_Dodojr_f18:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        sw	a0,24(sp)
        jal	0x8002f828
        li	a1,14369
        lw	a0,24(sp)
        li	at,-2
        lw	t6,4(a0)
        and	t7,t6,at
        jal	0x809f6a20
        sw	t7,4(a0)
        lw	a0,24(sp)
        lui	t8,0x809f
        addiu	t8,t8,31416
        sw	t8,400(a0)
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f18
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f70e8
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f19
        .ent            En_Dodojr_f19

En_Dodojr_f19:        

        addiu	sp,sp,-48
        sw	ra,36(sp)
        sw	s0,32(sp)
        lw	v0,400(a0)
        lui	t6,0x809f
        addiu	t6,t6,30524
        move	s0,a0
        beq	t6,v0,0x809f7158
        move	a2,a1
        lui	t7,0x809f
        addiu	t7,t7,30636
        beq	t7,v0,0x809f7158
        lui	t8,0x809f
        addiu	t8,t8,30796
        beq	t8,v0,0x809f7158
        lui	t9,0x809f
        addiu	t9,t9,31232
        beq	t9,v0,0x809f7158
        lui	t0,0x809f
        addiu	t0,t0,31416
        beq	t0,v0,0x809f7158
        lui	t1,0x809f
        addiu	t1,t1,31548
        beq	t1,v0,0x809f7158
        lui	t2,0x809f
        addiu	t2,t2,31716
        bnel	t2,v0,0x809f7164
        lbu	t3,7206(a2)
        b	0x809f7290
        move	v0,zero
        lbu	t3,7206(a2)
        lui	t4,0x809f
        addiu	t4,t4,29612
        beqzl	t3,0x809f71a4
        lbu	v1,421(s0)
        beq	t4,v0,0x809f7198
        lui	t5,0x809f
        addiu	t5,t5,29892
        bne	t5,v0,0x809f7190
        lui	t6,0x8003
        addiu	t6,t6,-18964
        sw	t6,192(s0)
        jal	0x809f709c
        move	a0,s0
        b	0x809f7290
        move	v0,zero
        lbu	v1,421(s0)
        lui	t9,0x809f
        addiu	t9,t9,29612
        andi	t7,v1,0x2
        bnez	t7,0x809f71c0
        andi	t8,v1,0xfffd
        b	0x809f7290
        move	v0,zero
        beq	t9,v0,0x809f71d4
        sb	t8,421(s0)
        lui	t0,0x809f
        addiu	t0,t0,29892
        bne	t0,v0,0x809f71e0
        lui	t1,0x8003
        addiu	t1,t1,-18964
        sw	t1,192(s0)
        lbu	v0,177(s0)
        li	at,1
        bnez	v0,0x809f7224
        nop
        lbu	t2,176(s0)
        move	a0,a2
        beqz	t2,0x809f7224
        nop
        jal	0x80032c7c
        move	a1,s0
        lui	t4,0x809f
        li	t3,2
        addiu	t4,t4,31816
        sh	t3,512(s0)
        sw	t4,400(s0)
        b	0x809f7290
        li	v0,1
        bnel	v0,at,0x809f7290
        move	v0,zero
        lw	v0,400(s0)
        lui	t5,0x809f
        addiu	t5,t5,30956
        beq	t5,v0,0x809f728c
        lui	v1,0x809f
        addiu	v1,v1,30828
        beq	v1,v0,0x809f728c
        move	a0,s0
        li	a1,14494
        jal	0x8002f828
        sw	v1,40(sp)
        li	t6,120
        sh	t6,510(s0)
        li	t7,120
        sw	t7,16(sp)
        move	a0,s0
        move	a1,zero
        li	a2,200
        jal	0x8003426c
        move	a3,zero
        jal	0x809f6a20
        move	a0,s0
        lw	t8,40(sp)
        sw	t8,400(s0)
        move	v0,zero
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,48
        jr	ra
        nop
        .end            En_Dodojr_f19
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f72a4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f20
        .ent            En_Dodojr_f20

En_Dodojr_f20:        

        addiu	sp,sp,-40
        sw	a1,44(sp)
        sw	ra,20(sp)
        addiu	a1,a0,404
        sw	a1,36(sp)
        jal	0x800626dc
        sw	a0,40(sp)
        lw	a3,40(sp)
        lui	t6,0x809f
        addiu	t6,t6,29612
        lw	v0,400(a3)
        lui	t7,0x809f
        addiu	t7,t7,31716
        beql	t6,v0,0x809f73a0
        lw	ra,20(sp)
        beq	t7,v0,0x809f739c
        lui	v1,0x809f
        addiu	v1,v1,29892
        beq	v1,v0,0x809f730c
        lui	t8,0x809f
        addiu	t8,t8,30092
        beq	t8,v0,0x809f730c
        lui	t9,0x809f
        addiu	t9,t9,31132
        bnel	t9,v0,0x809f733c
        lw	a0,44(sp)
        lw	a0,44(sp)
        lui	at,0x1
        ori	at,at,0x1e60
        lw	a2,36(sp)
        sw	v1,28(sp)
        sw	a3,40(sp)
        jal	0x8005d79c
        addu	a1,a0,at
        lw	a3,40(sp)
        lw	v1,28(sp)
        lw	v0,400(a3)
        lw	a0,44(sp)
        lui	at,0x1
        ori	at,at,0x1e60
        beq	v1,v0,0x809f7380
        addu	a1,a0,at
        lui	t0,0x809f
        addiu	t0,t0,30092
        beq	t0,v0,0x809f7380
        lui	t1,0x809f
        addiu	t1,t1,30828
        beq	t1,v0,0x809f7380
        lui	t2,0x809f
        addiu	t2,t2,30956
        beq	t2,v0,0x809f7380
        lui	t3,0x809f
        addiu	t3,t3,31132
        bne	t3,v0,0x809f7394
        nop
        lw	a2,36(sp)
        jal	0x8005d9f4
        sw	a1,24(sp)
        lw	a1,24(sp)
        lw	a0,44(sp)
        jal	0x8005dc4c
        lw	a2,36(sp)
        lw	ra,20(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        .end            En_Dodojr_f20
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f73ac
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f21
        .ent            En_Dodojr_f21

En_Dodojr_f21:        

        addiu	sp,sp,-48
        sw	s0,40(sp)
        move	s0,a0
        sw	ra,44(sp)
        lui	a0,0x600
        sw	a1,52(sp)
        jal	0x800a2000
        addiu	a0,a0,2144
        lui	at,0x43a0
        mtc1	at,$f8
        lwc1	$f6,144(s0)
        mtc1	v0,$f4
        lw	t6,52(sp)
        c.le.s	$f8,$f6
        cvt.s.w	$f2,$f4
        lw	v1,7236(t6)
        bc1tl	0x809f74b4
        lw	ra,44(sp)
        lwc1	$f10,40(s0)
        lwc1	$f16,40(v1)
        lui	at,0x4220
        mtc1	at,$f18
        sub.s	$f0,$f10,$f16
        lui	a1,0x600
        lui	a2,0x3fe6
        ori	a2,a2,0x6666
        c.le.s	$f18,$f0
        addiu	a1,a1,2144
        addiu	a0,s0,332
        li	a3,0
        bc1t	0x809f74b0
        li	t7,1
        lui	at,0xc120
        mtc1	at,$f4
        swc1	$f2,16(sp)
        sw	t7,20(sp)
        jal	0x800a51a0
        swc1	$f4,24(sp)
        move	a0,s0
        jal	0x8002f828
        li	a1,14372
        lui	at,0x4270
        mtc1	at,$f8
        lwc1	$f6,40(s0)
        lh	t0,48(s0)
        lw	t4,36(s0)
        sub.s	$f10,$f6,$f8
        addiu	t1,t0,-16384
        lw	t8,4(s0)
        sh	t1,48(s0)
        swc1	$f10,40(s0)
        lw	t3,40(s0)
        sw	t4,496(s0)
        lh	t2,48(s0)
        lw	t4,44(s0)
        lwc1	$f16,128(s0)
        lui	t5,0x809f
        addiu	t5,t5,29892
        ori	t9,t8,0x1
        sw	t3,500(s0)
        sw	t9,4(s0)
        sw	t5,400(s0)
        sh	t2,180(s0)
        sw	t4,504(s0)
        swc1	$f16,500(s0)
        lw	ra,44(sp)
        lw	s0,40(sp)
        addiu	sp,sp,48
        jr	ra
        nop
        .end            En_Dodojr_f21
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f74c4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f22
        .ent            En_Dodojr_f22

En_Dodojr_f22:        

        addiu	sp,sp,-48
        sw	s0,32(sp)
        move	s0,a0
        sw	ra,36(sp)
        sw	a1,52(sp)
        li	t6,100
        sw	t6,16(sp)
        move	a1,zero
        addiu	a0,a0,180
        li	a2,4
        jal	0x8007869c
        li	a3,1000
        lh	t7,180(s0)
        lui	at,0x4680
        mtc1	at,$f6
        mtc1	t7,$f4
        lui	at,0x4270
        mtc1	at,$f10
        cvt.s.w	$f0,$f4
        lwc1	$f8,12(s0)
        move	a0,s0
        li	a2,3
        div.s	$f0,$f0,$f6
        mul.s	$f16,$f10,$f0
        add.s	$f18,$f8,$f16
        swc1	$f18,40(s0)
        swc1	$f0,44(sp)
        jal	0x809f6510
        lw	a1,52(sp)
        lwc1	$f0,44(sp)
        mtc1	zero,$f4
        lui	t8,0x8003
        addiu	t8,t8,-18964
        c.eq.s	$f0,$f4
        lui	at,0x809f
        bc1fl	0x809f757c
        lw	ra,36(sp)
        lh	t9,180(s0)
        sw	t8,192(s0)
        lui	t0,0x809f
        sh	t9,48(s0)
        lwc1	$f6,32652(at)
        addiu	t0,t0,30092
        sw	t0,400(s0)
        swc1	$f6,104(s0)
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,48
        jr	ra
        nop
        .end            En_Dodojr_f22
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f758c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f23
        .ent            En_Dodojr_f23

En_Dodojr_f23:        

        addiu	sp,sp,-32
        sw	ra,28(sp)
        sw	s0,24(sp)
        move	s0,a0
        jal	0x8002d868
        sw	a1,36(sp)
        move	a0,s0
        lw	a1,36(sp)
        jal	0x809f6730
        addiu	a2,s0,36
        lh	v0,516(s0)
        move	a0,s0
        bnez	v0,0x809f75cc
        addiu	t6,v0,-1
        b	0x809f75d4
        move	v1,zero
        sh	t6,516(s0)
        lh	v1,516(s0)
        bnez	v1,0x809f75ec
        nop
        jal	0x8002f828
        li	a1,14370
        li	t7,5
        sh	t7,516(s0)
        jal	0x809f6dd0
        move	a0,s0
        beqz	v0,0x809f7614
        move	a0,s0
        jal	0x809f6c24
        move	a0,s0
        lui	t8,0x809f
        addiu	t8,t8,30348
        b	0x809f7678
        sw	t8,400(s0)
        jal	0x809f6e54
        lw	a1,36(sp)
        jal	0x809f706c
        move	a0,s0
        beqz	v0,0x809f7648
        move	a0,s0
        jal	0x8002f828
        li	a1,14368
        jal	0x809f6b38
        move	a0,s0
        lui	t9,0x809f
        addiu	t9,t9,31132
        sw	t9,400(s0)
        lhu	t0,136(s0)
        move	a0,s0
        andi	t1,t0,0x8
        beqzl	t1,0x809f767c
        lw	ra,28(sp)
        jal	0x8002f828
        li	a1,14371
        jal	0x809f6bbc
        move	a0,s0
        lui	t2,0x809f
        addiu	t2,t2,31232
        sw	t2,400(s0)
        lw	ra,28(sp)
        lw	s0,24(sp)
        addiu	sp,sp,32
        jr	ra
        nop
        .end            En_Dodojr_f23
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f768c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f24
        .ent            En_Dodojr_f24

En_Dodojr_f24:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        sw	a1,28(sp)
        lwc1	$f4,356(a0)
        move	a2,a0
        li	a1,14416
        trunc.w.s	$f6,$f4
        mfc1	t7,$f6
        nop
        sll	t8,t7,0x10
        sra	t9,t8,0x10
        addiu	t0,t9,-8
        slti	at,t0,4
        beqzl	at,0x809f76fc
        move	a0,a2
        lw	v0,480(a0)
        lh	t1,504(v0)
        addiu	t2,t1,1
        sh	t2,504(v0)
        lw	t5,484(a0)
        lw	t3,480(a0)
        sw	t5,36(t3)
        lw	t4,488(a0)
        sw	t4,40(t3)
        lw	t5,492(a0)
        b	0x809f772c
        sw	t5,44(t3)
        move	a0,a2
        jal	0x8002f828
        sw	a2,24(sp)
        lw	a2,24(sp)
        jal	0x8002d570
        lw	a0,480(a2)
        lw	a2,24(sp)
        lui	t7,0x809f
        li	t6,24
        addiu	t7,t7,30524
        sh	t6,514(a2)
        sh	zero,508(a2)
        sw	t7,400(a2)
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f24
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f773c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f25
        .ent            En_Dodojr_f25

En_Dodojr_f25:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        sw	a1,28(sp)
        lh	v0,514(a0)
        bnez	v0,0x809f775c
        addiu	t6,v0,-1
        b	0x809f7764
        move	v1,zero
        sh	t6,514(a0)
        lh	v1,514(a0)
        bnezl	v1,0x809f77a0
        lw	ra,20(sp)
        jal	0x809f64d0
        sw	a0,24(sp)
        lw	a0,24(sp)
        li	at,-2
        lw	t7,4(a0)
        and	t8,t7,at
        jal	0x809f6a20
        sw	t8,4(a0)
        lw	a0,24(sp)
        lui	t9,0x809f
        addiu	t9,t9,30636
        sw	t9,400(a0)
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f25
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f77ac
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f26
        .ent            En_Dodojr_f26

En_Dodojr_f26:        

        addiu	sp,sp,-32
        sw	ra,28(sp)
        sw	s0,24(sp)
        sw	a1,36(sp)
        lbu	t6,276(a0)
        move	s0,a0
        lui	at,0x4f80
        mtc1	t6,$f4
        bgez	t6,0x809f77e0
        cvt.s.w	$f6,$f4
        mtc1	at,$f8
        nop
        add.s	$f6,$f6,$f8
        lui	at,0x4100
        mtc1	at,$f10
        lui	at,0x809f
        lwc1	$f18,32656(at)
        div.s	$f16,$f6,$f10
        move	a0,s0
        mul.s	$f4,$f18,$f16
        jal	0x8002d868
        swc1	$f4,520(s0)
        move	a0,s0
        jal	0x809f68b0
        lw	a1,36(sp)
        beqz	v0,0x809f7838
        li	t7,60
        sh	t7,514(s0)
        jal	0x809f6ac4
        move	a0,s0
        lui	t9,0x809f
        li	t8,7
        addiu	t9,t9,30796
        sh	t8,508(s0)
        sw	t9,400(s0)
        lw	ra,28(sp)
        lw	s0,24(sp)
        addiu	sp,sp,32
        jr	ra
        nop
        .end            En_Dodojr_f26
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f784c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f27
        .ent            En_Dodojr_f27

En_Dodojr_f27:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        jal	0x809f7b3c
        nop
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f27
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f786c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f28
        .ent            En_Dodojr_f28

En_Dodojr_f28:        

        addiu	sp,sp,-40
        sw	ra,36(sp)
        sw	s0,32(sp)
        move	s0,a0
        jal	0x8002d868
        sw	a1,44(sp)
        move	a0,s0
        jal	0x809f68b0
        lw	a1,44(sp)
        beqzl	v0,0x809f78b0
        li	t7,10
        jal	0x809f6ac4
        move	a0,s0
        lui	t6,0x809f
        addiu	t6,t6,30956
        sw	t6,400(s0)
        li	t7,10
        sw	t7,16(sp)
        addiu	a0,s0,182
        move	a1,zero
        li	a2,4
        jal	0x8007869c
        li	a3,1000
        lh	t8,180(s0)
        lh	t9,510(s0)
        sh	t8,48(s0)
        sb	t9,276(s0)
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        .end            En_Dodojr_f28
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f78ec
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f29
        .ent            En_Dodojr_f29

En_Dodojr_f29:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        sw	a1,28(sp)
        lh	v0,510(a0)
        bnez	v0,0x809f790c
        addiu	t6,v0,-1
        b	0x809f7918
        move	v1,zero
        sh	t6,510(a0)
        lh	v0,510(a0)
        move	v1,v0
        beqz	v1,0x809f7974
        slti	at,v0,30
        beqz	at,0x809f798c
        andi	t7,v0,0x1
        beqz	t7,0x809f7954
        lui	at,0x3fc0
        lui	at,0x3fc0
        mtc1	at,$f0
        lwc1	$f4,36(a0)
        lwc1	$f8,44(a0)
        add.s	$f6,$f4,$f0
        add.s	$f10,$f8,$f0
        swc1	$f6,36(a0)
        b	0x809f798c
        swc1	$f10,44(a0)
        mtc1	at,$f0
        lwc1	$f16,36(a0)
        lwc1	$f4,44(a0)
        sub.s	$f18,$f16,$f0
        sub.s	$f6,$f4,$f0
        swc1	$f18,36(a0)
        b	0x809f798c
        swc1	$f6,44(a0)
        jal	0x809f6994
        sw	a0,24(sp)
        lw	a0,24(sp)
        lui	t8,0x809f
        addiu	t8,t8,30092
        sw	t8,400(a0)
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f29
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f799c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f30
        .ent            En_Dodojr_f30

En_Dodojr_f30:        

        addiu	sp,sp,-32
        sw	ra,28(sp)
        sw	s0,24(sp)
        sw	a1,36(sp)
        lw	t6,4(a0)
        lui	at,0x100
        move	s0,a0
        or	t7,t6,at
        jal	0x8002d868
        sw	t7,4(a0)
        move	a0,s0
        jal	0x809f68b0
        lw	a1,36(sp)
        beqzl	v0,0x809f79f0
        lw	ra,28(sp)
        jal	0x809f6994
        move	a0,s0
        lui	t8,0x809f
        addiu	t8,t8,30092
        sw	t8,400(s0)
        lw	ra,28(sp)
        lw	s0,24(sp)
        addiu	sp,sp,32
        jr	ra
        nop
        .end            En_Dodojr_f30
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7a00
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f31
        .ent            En_Dodojr_f31

En_Dodojr_f31:        

        addiu	sp,sp,-40
        sw	s0,32(sp)
        move	s0,a0
        sw	ra,36(sp)
        sw	a1,44(sp)
        li	t6,100
        sw	t6,16(sp)
        li	a1,16384
        addiu	a0,a0,180
        li	a2,4
        jal	0x8007869c
        li	a3,1000
        lh	v0,514(s0)
        li	t8,30
        bnez	v0,0x809f7a48
        addiu	t7,v0,-1
        b	0x809f7a54
        move	v1,zero
        sh	t7,514(s0)
        lh	v0,514(s0)
        move	v1,v0
        beqz	v1,0x809f7a8c
        subu	t9,t8,v0
        mtc1	t9,$f4
        lui	at,0x41f0
        mtc1	at,$f8
        cvt.s.w	$f6,$f4
        lui	at,0x4270
        mtc1	at,$f16
        lwc1	$f10,12(s0)
        div.s	$f0,$f6,$f8
        mul.s	$f18,$f16,$f0
        sub.s	$f4,$f10,$f18
        b	0x809f7a94
        swc1	$f4,40(s0)
        jal	0x8002d570
        move	a0,s0
        move	a0,s0
        lw	a1,44(sp)
        jal	0x809f6510
        li	a2,3
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        .end            En_Dodojr_f31
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7ab8
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f32
        .ent            En_Dodojr_f32

En_Dodojr_f32:        

        addiu	sp,sp,-40
        sw	ra,36(sp)
        sw	s0,32(sp)
        move	s0,a0
        jal	0x8002d868
        sw	a1,44(sp)
        li	t6,10
        sw	t6,16(sp)
        addiu	a0,s0,182
        move	a1,zero
        li	a2,4
        jal	0x8007869c
        li	a3,1000
        lh	t7,180(s0)
        move	a0,s0
        sh	t7,48(s0)
        jal	0x809f68b0
        lw	a1,44(sp)
        beqz	v0,0x809f7b28
        li	t8,60
        sh	t8,514(s0)
        jal	0x809f6ac4
        move	a0,s0
        lui	t0,0x809f
        li	t9,7
        addiu	t0,t0,31548
        sh	t9,508(s0)
        sw	t0,400(s0)
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        .end            En_Dodojr_f32
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7b3c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f33
        .ent            En_Dodojr_f33

En_Dodojr_f33:        

        addiu	sp,sp,-56
        sw	ra,52(sp)
        sw	s0,48(sp)
        lh	v0,508(a0)
        move	s0,a0
        li	a2,16
        beqzl	v0,0x809f7b8c
        lwc1	$f4,40(s0)
        lbu	t6,276(a0)
        li	a1,16384
        li	a2,200
        bnez	t6,0x809f7bd0
        move	a3,zero
        jal	0x8003426c
        sw	v0,16(sp)
        lh	t7,508(s0)
        addiu	t8,t7,-1
        b	0x809f7bd0
        sh	t8,508(s0)
        lwc1	$f4,40(s0)
        lw	a3,36(s0)
        addiu	a0,a1,7204
        swc1	$f4,16(sp)
        lwc1	$f6,44(s0)
        sw	zero,36(sp)
        sw	zero,32(sp)
        sw	zero,28(sp)
        sw	zero,24(sp)
        jal	0x80031f50
        swc1	$f6,20(sp)
        beqz	v0,0x809f7bc0
        li	t9,8
        sh	zero,504(v0)
        lui	t0,0x809f
        addiu	t0,t0,31716
        sh	t9,514(s0)
        sw	t0,400(s0)
        lw	ra,52(sp)
        lw	s0,48(sp)
        addiu	sp,sp,56
        jr	ra
        nop
        .end            En_Dodojr_f33
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7be4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f34
        .ent            En_Dodojr_f34

En_Dodojr_f34:        

        addiu	sp,sp,-32
        sw	ra,28(sp)
        sw	s0,24(sp)
        sw	a1,36(sp)
        lh	v0,514(a0)
        move	s0,a0
        move	a1,zero
        bnez	v0,0x809f7c10
        addiu	t6,v0,-1
        b	0x809f7c18
        move	v1,zero
        sh	t6,514(s0)
        lh	v1,514(s0)
        bnez	v1,0x809f7c34
        lw	a0,36(sp)
        addiu	a2,s0,36
        jal	0x8001f940
        li	a3,64
        jal	0x8002d570
        move	a0,s0
        lw	ra,28(sp)
        lw	s0,24(sp)
        addiu	sp,sp,32
        jr	ra
        nop
        .end            En_Dodojr_f34
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7c48
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f35
        .ent            En_Dodojr_f35

En_Dodojr_f35:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        sw	a1,28(sp)
        lh	v0,512(a0)
        bnez	v0,0x809f7c68
        addiu	t6,v0,-1
        b	0x809f7c70
        move	v1,zero
        sh	t6,512(a0)
        lh	v1,512(a0)
        bnezl	v1,0x809f7c84
        lw	ra,20(sp)
        jal	0x809f709c
        nop
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f35
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7c90
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f36
        .ent            En_Dodojr_f36

En_Dodojr_f36:        

        addiu	sp,sp,-40
        sw	s0,32(sp)
        move	s0,a0
        sw	ra,36(sp)
        sw	a1,44(sp)
        jal	0x800a49fc
        addiu	a0,a0,332
        jal	0x8002d8e0
        move	a0,s0
        move	a0,s0
        jal	0x809f70e8
        lw	a1,44(sp)
        lw	v0,400(s0)
        lui	t6,0x809f
        addiu	t6,t6,29612
        beql	t6,v0,0x809f7d1c
        move	a0,s0
        lh	t7,468(s0)
        lh	t8,470(s0)
        mtc1	zero,$f8
        mtc1	t7,$f4
        mtc1	t8,$f6
        li	t9,5
        cvt.s.w	$f4,$f4
        sw	t9,20(sp)
        lw	a0,44(sp)
        move	a1,s0
        swc1	$f8,16(sp)
        cvt.s.w	$f6,$f6
        mfc1	a2,$f4
        mfc1	a3,$f6
        jal	0x8002e4b4
        nop
        lw	v0,400(s0)
        move	a0,s0
        jalr	v0
        lw	a1,44(sp)
        move	a0,s0
        jal	0x8002d5b8
        lui	a1,0x4120
        move	a0,s0
        jal	0x809f72a4
        lw	a1,44(sp)
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        .end            En_Dodojr_f36
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7d50
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f37
        .ent            En_Dodojr_f37

En_Dodojr_f37:        

        addiu	sp,sp,-48
        lui	t7,0x809f
        sw	ra,20(sp)
        sw	a0,48(sp)
        sw	a2,56(sp)
        sw	a3,60(sp)
        addiu	t7,t7,32612
        lw	t9,0(t7)
        addiu	t6,sp,32
        lw	t8,4(t7)
        sw	t9,0(t6)
        lw	t9,8(t7)
        li	at,1
        sw	t8,4(t6)
        bne	a1,at,0x809f7dcc
        sw	t9,8(t6)
        lw	t0,68(sp)
        lui	at,0x3f80
        mtc1	at,$f2
        lui	at,0x3f00
        mtc1	at,$f4
        lwc1	$f0,520(t0)
        sw	a1,52(sp)
        li	a3,1
        mul.s	$f6,$f0,$f4
        add.s	$f14,$f0,$f2
        add.s	$f12,$f6,$f2
        mfc1	a2,$f12
        jal	0x800d0a8c
        nop
        lw	a1,52(sp)
        li	at,4
        bnel	a1,at,0x809f7dec
        lw	ra,20(sp)
        lw	a1,68(sp)
        addiu	a0,sp,32
        jal	0x800d1af4
        addiu	a1,a1,484
        lw	ra,20(sp)
        addiu	sp,sp,48
        move	v0,zero
        jr	ra
        nop
        .end            En_Dodojr_f37
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7dfc
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f38
        .ent            En_Dodojr_f38

En_Dodojr_f38:        

        sw	a0,0(sp)
        sw	a1,4(sp)
        sw	a2,8(sp)
        jr	ra
        sw	a3,12(sp)
        .end            En_Dodojr_f38
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

        /*
        *# Original address: 0x809f7e10
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f39
        .ent            En_Dodojr_f39

En_Dodojr_f39:        

        addiu	sp,sp,-40
        sw	ra,36(sp)
        sw	s0,32(sp)
        sw	a1,44(sp)
        lw	v0,400(a0)
        lui	t6,0x809f
        addiu	t6,t6,29612
        beq	t6,v0,0x809f7e74
        move	s0,a0
        lui	t7,0x809f
        addiu	t7,t7,31716
        beql	t7,v0,0x809f7e78
        lw	ra,36(sp)
        jal	0x80093d18
        lw	a0,0(a1)
        lui	t9,0x809f
        addiu	t9,t9,32252
        lw	a1,336(s0)
        lw	a2,364(s0)
        lui	a3,0x809f
        addiu	a3,a3,32080
        sw	s0,20(sp)
        sw	t9,16(sp)
        jal	0x800a15c8
        lw	a0,44(sp)
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,40
        jr	ra
        nop
        
        .end            En_Dodojr_f39
        .set            at
        .set            reorder


    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */

/* TODO: Add data (and possibly rodata?) section */
