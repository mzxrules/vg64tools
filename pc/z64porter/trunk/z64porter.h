#ifndef _Z64_PORTER_H_
 #define _Z64_PORTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <z64.h>
#include <n64rom.h>
#include "strint.h"

/* Macros */
#define U32(x)	( ((x)[0]<<24)|((x)[1]<<16)|((x)[2]<<8)|(x)[3])
#define U24(x)	(((x)[0]<<16)|((x)[1]<<8)|((x)[2]))
#define U16(x)	(((x)[0]<<8)|((x)[1]))
#define setU16(x,val)			\
{					\
	(x)[0] = ((val)>>8) & 0xFF;	\
	(x)[1] = (val) & 0xFF;		\
}
#define setU32(x,val)			\
{					\
	(x)[0] = ((val)>>24) & 0xFF;	\
	(x)[1] = ((val)>>16) & 0xFF;	\
	(x)[2] = ((val)>>8) & 0xFF;	\
	(x)[3] = (val) & 0xFF;		\
}

/* Zelda level header values */
#define ZLH_ENTRANCES	0x00
#define ZLH_ACTORS	0x01
#define ZLH_UNK02	0x02
#define ZLH_COLLISION	0x03
#define ZLH_MAPS	0x04
#define ZLH_UNK05	0x05
#define ZLH_ENTRANCESINDEX	0x06
#define ZLH_OUTSIDESET	0x07
#define ZLH_OBJSETC	0x08
#define ZLH_MESH	0x0A
#define ZLH_OBJECTS	0x0B
#define ZLH_UNK0C	0x0C
#define ZLH_DOORS	0x0E
#define ZLH_ENVSET	0x0F
#define ZLH_TIME	0x10
#define ZLH_SKYSET	0x11
#define ZLH_SKYCONTROL	0x12
#define ZLH_EXITS	0x13
#define ZLH_END		0x14
#define ZLH_MUSIC	0x15
#define ZLH_ECHO	0x16
#define ZLH_UNK17	0x17
#define ZLH_ALT_HEADERS	0x18
#define ZLH_UNK19	0x19

/* Actor maximum values */
#define OOT_ACT_MAX	470
#define MM_ACT_MAX	689

/* Object maximum values */
#define OOT_OBJ_MAX	401
#define MM_OBJ_MAX	642

/* Default actor numbers */
#define OOT_ACT_FLAME	8
#define OOT_ACT_DOOR	9
#define MM_ACT_FLAME	4
#define MM_ACT_DOOR	5

/* Maximum music values */
#define MAX_MUSIC_OOT	0x6C
#define MAX_MUSIC_MM	0x7F

#ifdef DEBUG
 #define dump(x, fmt) fprintf(stderr, "%s: %s=" fmt ";\n", __FILE__, #x, x)
#else
 #define dump(x, fmt)
#endif

/* error - display and quit */
#define error(...)\
{\
    fprintf(stderr, "error: ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");\
    cleanup();\
    exit(EXIT_FAILURE);\
}

/* message */
#define msg(pri, ...)\
if(verbose >= pri)\
{\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");\
}

/* Check allocated memory - error if null */
#define check_mem(mem) if(mem == NULL) error("cannot allocate memory (%i in %s)", __LINE__ - 1, __FUNCTION__)

int verbose;

/* functions */
void cleanup();
void parse_args(int argc, char ** argv);
void check_setup();

#endif /* _Z64_PORTER_H_ */
