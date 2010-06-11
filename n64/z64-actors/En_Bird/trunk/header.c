#include <mips.h>
#include <stdio.h>
#include <actor.h>
#include "bird.h"

/*
 00000420  00 72 06 00 00 00 00 00  00 77 00 00 00 00 01 dc  |.r.......w......|
 00000430  80 9c 1b b8 80 9c 1c a0  80 9c 1f 5c 80 9c 1f 8c  |...........\....|
*/

MK_AHEAD
(
	header,
	0x72,
	0x06,
	0,
	0,
	0x77,
	0x1DC,
	
	En_Bird_f2,
	En_Bird_f3,
	En_Bird_f8,
	En_Bird_f9
);

u32 En_Bird_dat1[] = {0x304c15e0, 0x00000000, 0x00000420, 0x00000000};
