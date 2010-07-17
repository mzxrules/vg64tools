#ifndef _Z64_PORTER_H_
 #define _Z64_PORTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <z64.h>
#include <n64rom.h>
#include "strint.h"

#define MUSIC_MAX_OOT	0x6C
#define MUSIC_MAX_MM	0x7F

/* error - display and quit */
#define error(...)\
{\
    cleanup();\
    fprintf(stderr, "z64porter: ");\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");\
    exit(EXIT_FAILURE);\
}

/* message */
#define msg(pri, ...)\
if(verbose >= pri)\
{\
    fprintf(stderr, __VA_ARGS__);\
    fprintf(stderr, "\n");\
}

int verbose;

/* functions */
void cleanup();
void parse_args(int argc, char ** argv);
void check_setup();

#endif /* _Z64_PORTER_H_ */
