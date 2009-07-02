/***************************
* ZELDA RESOURCE EXTRACTOR *
****************************
-> zre.h                  */

/* Include guard */
#ifndef __ZRE_H
#define __ZRE_H

/* Inclues */
#include <stdio.h>
#include "z64l/z64lib.h"
#include "inc/msg.h"

/* Shorthand var types */
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char   u8;
typedef int   s32;
typedef short s16;
typedef char   s8;

/* Defines */
enum { false, true };
#define __BUILD_NUM     3001
#define __ODIR_DEFAULT "data"

/* Configuration struct */
struct config {
	u8 silent;
	u8 offsets;
	u8*odir;
	u8 debug;
	u8 fid; /* 0 = none, 1 = relative to file table, 2 = r to files ext */
	u8 nwrite;
	u8 display_info;
	u8 skip_names;
	u8 strip;
	u8 filter;
	u8 crc; /* hmm... perhaps done automatically? */
	u8 yta; /* yes to all */
	u8 uot;
	u8 blen;
	u8 notable; /* do not try scene/actor table */
	u8 noscene;
	u8 noactor;
};

/* Statistics struct */
struct statistics {
	u32 files_extracted;
	u32 amt_processed;
};

/* Scene manager struct */
struct scenetman {
	u32 status;
	u32 pos;
};
	

/* Macros */
#define DRAWBAR(a,b,c,d,e,f,g) { \
	if(!conf.debug) { (g)=draw_bar(a,b,c,d,e,f); } \
}
#define ZNT_READ_NEXT(x) { if(!conf.skip_names) \
	z64nt_read_next(x); \
}
#define ERROR(x, ...) { if(!conf.uot){ \
	fprintf(stderr, "\nError encountered in %s:%u -\n" x "Press enter to " \
	"quit.\n", __FILE__, __LINE__, ##__VA_ARGS__); GETINPUT(); exit(0); \
	}else{ exit(-1); } \
}

/* debug with alternate action */
#define DEBUGA(x,y) { if(conf.debug){ \
	x; } else { y; } \
}
/* plain 'ol debug */
#define DEBUG(x) { if(conf.debug){ \
	x; } \
}
/* forced message */
#define FMESSAGE(x, ...) { \
	printf(x, ##__VA_ARGS__); \
} 
#define WRITE_OUTPUT_FILE(a,b,c,d) { if(!conf.nwrite) {\
	if(!((b) = fopen((a),"wb"))) \
		ERROR("Unable to open file \"%s\" for writing. The error returned was:\n%s\n", \
		(a),strerror(errno)); \
	fseek((b),0,SEEK_SET); \
	fwrite((c), 1, (d), (b)); \
	fclose(b); \
} }
#define BYTES2LONG(x) ((x)[0] << 24 | \
                       (x)[1] << 16 | \
                       (x)[2] << 8  | \
                       (x)[3])

/* Global variables */
extern struct config conf;
extern struct statistics stats;
extern char *filename;
extern u32 rfilesize, rident;
extern char output_filename[];
extern FILE *fhandle;
extern Z64FS *fsh;
extern Z64NT *nth;
extern Z64FB fbuff;

/* ~~~~ Function overview ~~~~ */
/* => rom.c */
void zre_rom_check ( void );
void zre_rom_swap ( void );
int zre_rom_ident_name ( void );
/* => args.c */
int zre_handle_arguments ( int argc, char **argv );
/* => procedures.c */
void zre_proc_get_filename ( void );
void zre_proc_prepare_name ( void );
int  zre_proc_offsetcheck  ( void );
int  zre_proc_get_filetype ( void );
int  zre_proc_handle_tables( void );
/* => progbar.c */
u16 draw_bar (s32 bar_length, s32 min, s32 max, s32 current, u8 type, u8 show);
/* => functions.c */
u8 str_replace (u8 *search_str, u8 *replace_str, u8 *source_str);
/* => scenet.c */
int zre_scene_main ( void );
/* => actort.c */
int zre_actor_main   ( void  );
int zre_actor_search ( u32 s );
/* => termio.c */
void MESSAGE (const char *format, ...);
int GETINPUT ( void );
int READTOSTR ( char *str, int maxlen );

#endif /* __ZRE_H */
