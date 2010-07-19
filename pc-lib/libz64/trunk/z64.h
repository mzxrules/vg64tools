/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   z64dev/libz64 - z64.h                                                 *
 *   z64dev project page: http://z64dev.sourceforge.net/                   *
 *   Copyright (C) 2009 ZZT32                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
#ifndef __LZ64_H__
#define __LZ64_H__


/* ----------------------------------------------
   Dependent headers
   ---------------------------------------------- */

#include <stdio.h>
#include <glib.h>
#include <n64rom.h>
#include <z64fs.h>
#include <z64nt.h>
#include <z64at.h>
#include <z64st.h>
#include <z64detect.h>
#include <z64yaz0.h>


/* ----------------------------------------------
   Constants/macros
   ---------------------------------------------- */

/* Handle macros */
#define Z_FS_COUNT( z )			((z)->fs->filecount)

/* Filesystem macros */
#define Z_PHYS_START( e )       ((e)->start)
#define Z_PHYS_END( e )       	(!(e)->end ? Z_PHYS_START(e) + Z_FILESIZE_VIRT(e) : (e)->end)
#define Z_VIRT_START( e )		((e)->vstart)
#define Z_VIRT_END( e )			((e)->vend)
#define Z_FILESIZE_VIRT( e )	(Z_VIRT_END(e) - Z_VIRT_START(e))
#define Z_FILESIZE_PHYS( e )	(Z_PHYS_END(e) - Z_PHYS_START(e))
#define Z_COMPRESSED( e )		((e)->end)
#define Z_EXISTS( e )			((~Z_PHYS_START(e))|(~Z_PHYS_END(e)))

/* Status flags */
enum
{
	Z64_LOADED_FS   = 0x0001,
	Z64_LOADED_NT   = 0x0002,
	Z64_LOADED_AT   = 0x0004,
	Z64_LOADED_OT   = 0x0008,
	Z64_LOADED_ST   = 0x0010,
	Z64_LOADED_CODE = 0x0020,
	Z64_NO_CODE     = 0x0040
};


/* ----------------------------------------------
   Data types
   ---------------------------------------------- */

/* ROM context */
struct z64_t
{
	/* ROM information */
	char   * filename;
	FILE   * handle;
	int	     filesize;
	N64Rom * rom;

	/* Context status (what's loaded, errors etc) */
	int    status;
	char   errbuff[512];

	/* Filesystem element - basis */
	Z64FS * fs;

	/* Extra elements */
	Z64NT * nt;		/* Name table   */
	Z64AT * at;		/* Actor table  */
	void  * ot;		/* Object table */
	Z64ST * st;		/* Scene table  */

	/* Important files */
	const Z64FSEntry * f_code;			/* The game's Code file */
	guint8           * f_code_data;		/* Code file data 		*/

	/* Reserved... */
	int	resv1;
	int	resv2;
	int	resv3;
	int	resv4;
};

/* Alias */
typedef struct z64_t Z64;


/* ----------------------------------------------
   Function declarations
   ---------------------------------------------- */

extern Z64 * z64_open ( N64Rom * rom );
extern void z64_close ( Z64 * );
extern void z64_read_file ( Z64 *, int, unsigned char * );
extern gboolean z64_discover_code ( Z64 * );
extern Z64AT * z64at_open ( Z64 * );
extern Z64ST * z64st_open ( Z64 * );
extern const char * z64_set_error ( Z64 *, char *, ... );
extern const char * z64_error ( Z64 * );
extern void z64fs_read_file ( Z64 * h, int id, unsigned char * dest );
extern guint32 z64st_getstart( Z64 * h, int id);

#endif
