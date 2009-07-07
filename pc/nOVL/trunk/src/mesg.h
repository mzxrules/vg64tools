/*
*   nOVL -- mesg.h
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
#ifndef __NOVL_MESG_H__
#define __NOVL_MESG_H__

#include <stdarg.h>
#include "novl.h"
#include "ansi.h"

extern int mk_mesg_f ( char *, char *, va_list );
extern int mk_mesg ( char *, char *, ... );
extern int MESG ( char *, ... );
extern int ERROR ( char *, ... );

 #ifdef NOVL_DEBUG
  extern int DEBUG ( char *, ... );
  extern int DEBUG_R ( char *, ... );
 #else
  #define DEBUG(...)
  #define DEBUG_R(...)
 #endif /* NOVL_DEBUG */

#endif /* __NOVL_MESG_H__ */

