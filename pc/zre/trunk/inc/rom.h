/****************************
* ROM BYTESWAPPING/HANDLING *
****************************/

#ifndef __ROM_H
#define __ROM_H

#define __ENDIAN_BIG   0x80371240UL
#define __ENDIAN_SMALL 0x40123780UL
#define __ENDIAN_V64   0x37804012UL

#define __NAME_OOT1 "THE LEGEND OF ZELDA"
#define __NAME_OOT2 "LEGEND OF DEBUG"
#define __NAME_MM1 "ZELDA MAJORA'S MASK" /* normal english */
#define __NAME_MM2 "THE MASK OF MUJURA" /* japanese */
#define __NAME_MM3 "MAJORA'S MASK" /* demo ROM */

enum { __GAME_UNK, __GAME_OOT, __GAME_MM };

#define zre_rom_print_name(x) { \
	switch(x) { case __GAME_UNK: \
	MESSAGE("Unknown"); break; \
	case __GAME_OOT: \
	MESSAGE("Ocarina of Time"); break; \
	case __GAME_MM: \
	MESSAGE("Majora's Mask"); break; } \
}

#endif
