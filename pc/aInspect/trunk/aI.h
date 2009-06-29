/*
*   Zelda 64 Actor Inspector -- aI.h
*   Copyright (c) 2009  Marshall B. Rogers [mbr@64.vg]
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public
*   Licence along with this program; if not, write to the Free
*   Software Foundation, Inc., 51 Franklin Street, Fifth Floor, 
*   Boston, MA  02110-1301, USA
*/

#ifndef __ZACTOR_INSPECTOR_H__
#define __ZACTOR_INSPECTOR_H__

#include <stdint.h>


/* ----------------------------------------------
   Constants
   ---------------------------------------------- */

/* Section IDs */
enum ZASect
{
    ZA_TEXT,
    ZA_DATA,
    ZA_RODATA,
    ZA_BSS,
    ZA_SECT_COUNT
};

/* Program info */
#define PROGRAM_NAME    "aI"
#define PROGRAM_VERSION "v1.0.0"
#define VERSION_MAJOR   1
#define VERSION_MINOR   0
#define VERSION_MICRO   0


/* ----------------------------------------------
   Data types
   ---------------------------------------------- */

/* Section header found in an actor */
struct sect_header_t
{
    /* Offsets within file to different sections */
    uint32_t size[ZA_SECT_COUNT];
    
    /* Amount of relocations */
    uint32_t reloc;
};

/* Context for an open actor file */
struct zactor_h_t
{
    /* I/O */
    char * fname;
    FILE * fhandle;
    int fsize;
    
    /* Actor data */
    int h_offset;
    struct sect_header_t header;
};

/* A relocation */
struct zactor_reloc_t
{
    int section;
    int type;
    int address;
};

/* Type aliases */
typedef struct zactor_h_t ZAct;


/* ----------------------------------------------
   Global variables
   ---------------------------------------------- */

/* Textual representation of sections */
extern const char * za_section_names[];


/* ----------------------------------------------
   Functions
   ---------------------------------------------- */

/* aI related */
extern ZAct * za_open  ( char * );
extern void   za_close ( ZAct * );

/* Other */
extern int format_value ( char *, unsigned );
extern int MESG ( char *, ... );
extern int ERROR ( char * fmt, ... );
extern uint32_t get_val32 ( uint8_t * );


#endif /* __ZACTOR_INSPECTOR_H__ */

