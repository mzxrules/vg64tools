/*
*   Nintendo 64 Disassembler -- sym.h
*   Copyright (c) 2009  ZZT32 [mbr@64.vg]
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

#ifndef __SYM_H__
#define __SYM_H__

extern int longest_name;

extern int sym_load ( char * file );
extern const char * sym_lookup ( unsigned a );

#endif /* __SYM_H__ */
