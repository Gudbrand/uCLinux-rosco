/*
 * arch/m68knommu/platform/rosco/rosco_m68k/crt0_ram.S
 *
 * rosco_m68k Classic RAM kernel startup
 *
 * CPU: MC68010
 * RAM: 0x000000 - 0x4fffff (5 MiB)
 *
 * Kernel is loaded into RAM by the rosco firmware before entry here.
 */

#include <linux/config.h>

       .cpu 68010
        .text

        .global _start
        .global _stext

        .global _rambase
        .global _ramvec
        .global _ramstart
        .global _ramend

/*
 * Runtime memory-description variables expected by m68knommu.
 */
        .data
        .align  2

_rambase:
        .long   0

_ramvec:
        .long   0

_ramstart:
        .long   0

_ramend:
        .long   0

        .text
        .align  2

_start:
_stext:
        /*
         * Enter supervisor mode and mask interrupts while Linux
         * establishes its execution environment.
         */
        move.w  #0x2700,%sr

        /*
         * Temporary startup stack at top of physical RAM.
         *
         * Physical RAM:
         *     0x000000 - 0x4fffff
         */
        move.l  #0x00500000,%sp

        /*
         * Tell the generic m68knommu code where memory lives.
         *
         * _rambase  = beginning of physical RAM
         * _ramvec   = Linux vector table
         * _ramstart = first byte available after kernel image
         * _ramend   = exclusive end of physical RAM
         */
        move.l  #0x00000000,%d0
        move.l  %d0,_rambase

        move.l  #__ramvec,%d0
        move.l  %d0,_ramvec

        move.l  #_ebss,%d0
        move.l  %d0,_ramstart

        move.l  #0x00500000,%d0
        move.l  %d0,_ramend

        /*
         * MC68010 has a Vector Base Register.
         * Move exception/interrupt vectoring away from address zero
         * to Linux's own vector table.
         */
        move.l  #__ramvec,%d0
        movec   %d0,%vbr

        /*
         * Clear BSS.
         */
        move.l  #_sbss,%a0
        move.l  #_ebss,%a1

1:
        cmp.l   %a0,%a1
        bls     2f
        clr.l   (%a0)+
        bra     1b

2:
        /*
         * Use the normal initial Linux kernel stack.
         */
        lea     init_thread_union,%a0
        lea     0x2000(%a0),%sp

        /*
         * start_kernel() does not return.
         */
        jsr     start_kernel

3:
        bra     3b
