#include <mips.h>

        .text
        
        
#if 0        
        /*
        *# Original address: 0x809c1bb0
        */
        
        .set            noreorder
        .global         En_Bird_f1
        .ent            En_Bird_f1

En_Bird_f1:
        
        jr              $ra
        sw              a1,400(a0)
        
        .end            En_Bird_f1
        .set            reorder
        
#endif
    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
        
        
        /*
        *# Original address: 0x809c1bb8
        */
#if 0
        .set            noreorder
        .set            noat
        .global         En_Bird_f2
        .ent            En_Bird_f2

En_Bird_f2:

        addiu           $sp,$sp,-48
        sw              a1,52($sp)
        sw              $ra,44($sp)
        sw              s0,40($sp)
        la              a1,En_Bird_dat1
        jal             0x800780dc
        move            s0,a0
        lui             a1,0x3c23
        ori             a1,a1,0xd70a
        jal             0x8002d62c
        move            a0,s0
        lui             a2,0x600
        lui             a3,0x600
        addiu           a3,a3,108
        addiu           a2,a2,8592
        lw              a0,52($sp)
        addiu           a1,s0,332
        sw              $zero,16($sp)
        sw              $zero,20($sp)
        jal             0x800a457c
        sw              $zero,24($sp)
        lui             a1,0x45ab
        lui             a2,0x8003
        addiu           a2,a2,-18964
        ori             a1,a1,0xe000
        addiu           a0,s0,180
        jal             0x8002b1e0
        lui             a3,0x4080
        lui             $at,0x3fc0
        mtc1            $at,$f4
        lui             $at,0x3f00
        mtc1            $at,$f6
        lui             $at,0x4220
        mtc1            $zero,$f0
        mtc1            $at,$f8
        lui             $at,0x428c
        mtc1            $at,$f10
        li              t6,2500
        sw              $zero,404(s0)
        sw              $zero,408(s0)
        sh              t6,448(s0)
        sb              $zero,174(s0)
        move            a0,s0
        lh              a1,28(s0)
        swc1            $f4,424(s0)
        swc1            $f6,428(s0)
        swc1            $f0,416(s0)
        swc1            $f0,420(s0)
        swc1            $f0,440(s0)
        swc1            $f8,432(s0)
        jal             En_Bird_f4
        swc1            $f10,444(s0)
        lw              $ra,44($sp)
        lw              s0,40($sp)
        addiu           $sp,$sp,48
        jr              $ra
        nop
        
        .end            En_Bird_f2
        .set            at
        .set            noreorder
#endif
        
    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
        
    
        /*
        *# Original address: 0x809c1ca0
        */
#if 0
        .set            noreorder
        .global         En_Bird_f3
        .ent            En_Bird_f3

En_Bird_f3:
        
        sw              a0,0($sp)
        jr              $ra
        sw              a1,4($sp)
        
        .end            En_Bird_f3
        .set            reorder
        
#endif        
    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
        
        
        /*
        *# Original address: 0x809c1cac
        */
#if 1
        .set            noreorder
        .set            noat
        .global         En_Bird_f4
        .ent            En_Bird_f4
        
En_Bird_f4:
        
        addiu           $sp,$sp,-48
        sw              a0,48($sp)
        sw              $ra,36($sp)
        lui             a0,0x600
        sw              a1,52($sp)
        jal             0x800a2000
        addiu           a0,a0,108
        lw              t6,48($sp)
        mtc1            v0,$f4
        lui             $at,0x3f80
        lh              t7,412(t6)
        li              a0,5
        li              a1,35
        beqz            t7,$Lf4_01
        cvt.s.w         $f2,$f4
        mtc1            $zero,$f0
        b               $Lf4_02
        swc1            $f0,40($sp)
$Lf4_01:
        mtc1            $at,$f0
        nop
        swc1            $f0,40($sp)
$Lf4_02:
        jal             0x80077d90
        swc1            $f2,44($sp)
        lw              v1,48($sp)
        lwc1            $f0,40($sp)
        mtc1            $zero,$f12
        lwc1            $f2,44($sp)
        sw              v0,408(v1)
        lui             a1,0x600
        mfc1            a2,$f0
        mfc1            a3,$f12
        addiu           a1,a1,108
        sw              $zero,20($sp)
        addiu           a0,v1,332
        swc1            $f12,24($sp)
        jal             0x800a51a0
        swc1            $f2,16($sp)
        la              a1,En_Bird_f5
        jal             En_Bird_f1
        lw              a0,48($sp)
        lw              $ra,36($sp)
        addiu           $sp,$sp,48
        jr              $ra
        nop
        
        .end            En_Bird_f4
        .set            at
        .set            noreorder
        
#endif
    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
        
        
        /*
        *# Original address: 0x809c1d60
        */
#if 0
        .set            noreorder
        .set            noat
        .global         En_Bird_f5
        .ent            En_Bird_f5
        
En_Bird_f5:
        
        addiu           $sp,$sp,-40
        sw              $ra,36($sp)
        sw              s0,32($sp)
        sw              a1,44($sp)
        move            s0,a0
        jal             0x80100290
        lwc1            $f12,436(a0)
        lwc1            $f6,416(s0)
        lwc1            $f4,188(s0)
        mtc1            $zero,$f2
        mul.s           $f8,$f0,$f6
        lui             a2,0x3dcc
        mfc1            a1,$f2
        ori             a2,a2,0xcccd
        addiu           a0,s0,104
        lui             a3,0x3f00
        add.s           $f10,$f4,$f8
        swc1            $f10,188(s0)
        jal             0x80078310
        swc1            $f2,16($sp)
        lh              t6,412(s0)
        beqz            t6,$Lf5_01
        nop
        lwc1            $f0,104(s0)
        add.s           $f16,$f0,$f0
        swc1            $f16,360(s0)
$Lf5_01:
        jal             0x800a49fc
        addiu           a0,s0,332
        lw              t7,408(s0)
        move            a0,s0
        addiu           t8#if 0,t7,-1
        bgtz            t8,$Lf5_02
        sw              t8,408(s0)
        jal             En_Bird_f6
        lh              a1,28(s0)
$Lf5_02:
        lw              $ra,36($sp)
        lw              s0,32($sp)
        addiu           $sp,$sp,40
        jr              $ra
        nop

        .end            En_Bird_f5
        .set            at
        .set            noreorder
        
#endif
    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
        
        
        /*
        *# Original address: 0x809c1e00
        */
#if 0
        .set            noreorder
        .global         En_Bird_f6
        .ent            En_Bird_f6

En_Bird_f6:
        
        addiu           $sp,$sp,-24
        sw              $ra,20($sp)
        sw              a0,24($sp)
        sw              a1,28($sp)
        li              a1,45
        jal             0x80077d90
        li              a0,20
        lw              a0,24($sp)
        la              a1, En_Bird_f7
        jal             En_Bird_f1
        sw              v0,408(a0)
        lw              $ra,20($sp)
        addiu           $sp,$sp,24
        jr              $ra
        nop

        .end            En_Bird_f6
        .set            at
        .set            noreorder
        
#endif
    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
        
        
        /*
        *# Original address: 0x809c1e40
        */

        .set            noreorder
        .set            noat
        .global         En_Bird_f7
        .ent            En_Bird_f7       

En_Bird_f7:
        
                
        addiu           $sp,$sp,-56
        sw              $ra,36($sp)
        sw              s0,32($sp)
        sw              a1,60($sp)
        move            s0,a0
        jal             0x80100290
        lwc1            $f12,436(a0)
        lwc1            $f6,416(s0)
        lwc1            $f4,188(s0)
        mtc1            $zero,$f16
        mul.s           $f8,$f0,$f6
        lw              a1,424(s0)
        lui             a2,0x3dcc
        lw              a3,428(s0)
        ori             a2,a2,0xcccd
        addiu           a0,s0,104
        add.s           $f10,$f4,$f8
        swc1            $f10,188(s0)
        jal             0x80078310
        swc1            $f16,16($sp)
        addiu           a0,s0,36
        addiu           a1,s0,8
        sw              a1,40($sp)
        jal             0x80078028
        sw              a0,44($sp)
        lwc1            $f18,432(s0)
        lw              a0,44($sp)
        lw              a1,40($sp)
        c.lt.s          $f18,$f0
        nop
        bc1t            $Lf7_01
        nop
        lw              t6,408(s0)
        slti            $at,t6,4
        beqz            $at,$Lf7_02
        nop
$Lf7_01:
        jal             0x80078068
        nop
        sll             a1,v0,0x10
        sra             a1,a1,0x10
        addiu           a0,s0,50
        jal             0x80077b58
        lh              a2,448(s0)
        b               $Lf7_03
        lh              t3,50(s0)
$Lf7_02:
        jal             0x80100290
        lwc1            $f12,436(s0)
        lwc1            $f6,420(s0)
        lh              t7,50(s0)
        mul.s           $f4,$f0,$f6
        trunc.w.s       $f8,$f4
        mfc1            t1,$f8
        nop
        addu            t2,t7,t1
        sh              t2,50(s0)
        lh              t3,50(s0)
$Lf7_03:
        addiu           a0,s0,332
        jal             0x800a49fc
        sh              t3,182(s0)
        lw              t4,408(s0)
        move            a0,s0
        addiu           t5,t4,-1
        bgez            t5,$Lf7_04
        sw              t5,408(s0)
        jal             En_Bird_f4
        lh              a1,28(s0)
$Lf7_04:
        lw              $ra,36($sp)
        lw              s0,32($sp)
        addiu           $sp,$sp,56
        jr              $ra
        nop

        .end            En_Bird_f7
        .set            at
        .set            noreorder
        

    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
        
        
        /*
        *# Original address: 0x809c1f5c
        */
#if 0
        .set            noreorder
        .set            noat
        .global         En_Bird_f8
        .ent            En_Bird_f8
        
En_Bird_f8:
        
        addiu           $sp,$sp,-24
        sw              $ra,20($sp)
        lwc1            $f4,436(a0)
        lwc1            $f6,440(a0)
        lw              t9,400(a0)
        add.s           $f8,$f4,$f6
        jalr            t9
        swc1            $f8,436(a0)
        lw              $ra,20($sp)
        addiu           $sp,$sp,24
        jr              $ra
        nop
        
        .end            En_Bird_f8
        .set            at
        .set            noreorder    
#endif

    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
        
        
        /*
        *# Original address: 0x809c1f8c
        */
#if 0
        .set            noreorder
        .set            noat
        .global         En_Bird_f9
        .ent            En_Bird_f9

En_Bird_f9:
        
        addiu           $sp,$sp,-32
        sw              a0,32($sp)
        lw              t6,32($sp)
        sw              $ra,28($sp)
        sw              a1,36($sp)
        move            a0,a1
        lw              a1,336(t6)
        lw              a2,364(t6)
        sw              $zero,20($sp)
        sw              $zero,16($sp)
        jal             0x800a15c8
        move            a3,$zero
        lw              $ra,28($sp)
        addiu           $sp,$sp,32
        jr              $ra
        nop
        
        .end            En_Bird_f9
        .set            at
        .set            noreorder
        

    /* #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~# */
#endif
        
        /*
        *# Data; original addr: 0x809c1ff0
        */
        
        .data
        
        .global         En_Bird_dat1
        
En_Bird_dat1:

        .word   0x304c15e0
        .word   0x00000000
        .word   0x00000420
        .word   0x00000000

