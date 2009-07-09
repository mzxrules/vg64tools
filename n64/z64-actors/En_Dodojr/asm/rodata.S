#include <mips.h>
#include "../dodojr.h"

	.section	.rodata
	
	.global		En_Dodojr_rodata
	
En_Dodojr_rodata:

	.word 0x40266666
	.word 0xBF4CCCCD
	.word 0xBF4CCCCD
	.word 0xBF4CCCCD
	.word 0xBF4CCCCD
	.word 0xBF4CCCCD
	.word 0xBF4CCCCD
	.word 0x40266666
	.word 0x3F99999A
	
	# There were three more word heres (0), but I believe it is just padding
	# for the 16-byte alignment.

