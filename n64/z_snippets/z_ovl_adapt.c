/*
*   Rewritten `z_ovl_adapt` function
*   Addresses: 0x800FC2C0(DBG)
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

#include <stdio.h>
#include <stdint.h>


/* ----------------------------------------------
   Constants
   ---------------------------------------------- */

/* 
  Section IDs -- 
  Not used directly (except for count), but here for reference purposes. 
*/
enum
{
    S_TEXT,
    S_DATA,
    S_RODATA,
    S_BSS,
    S_COUNT
};

/* 
  Relocation types -- 
  There's room for more, but these are the only ones the game seems to implement
*/
#define R_PTR       2
#define R_J         4
#define R_PAIR1     5
#define R_PAIR2     6


/* ----------------------------------------------
   Data types
   ---------------------------------------------- */
   
/* Aliases */
typedef uint32_t u32;

/*
  Header structure -- 
  Overlay header describing the section sizes, the amount of relocations, and
  the relocations themselves.
*/
struct ovl_header
{
    u32 sizes[S_COUNT];
    int relocate_count;
    u32 relocations[];
};


/* ----------------------------------------------
   Global functions
   ---------------------------------------------- */

void
z_ovl_adapt ( void * data, struct ovl_header * ovl, void * ovl_base )
{
    int i, total, offset;
    u32 * section_sizes;
    void * section_addr[S_COUNT + 1];
    u32 pair_vals[32];
    u32 * pair_addrs[32];
    
    /* First one is initialized to zero */
    section_addr[0] = NULL;
    
    /* Memory offset */
    offset = (uint32_t)ovl_base - (uint32_t)data;
    
    /* Set pointer to section sizes... */
    section_sizes = ovl->sizes;
    
    /* Set the section addresses */
    for( i = 0, total = 0; i < S_COUNT; i++ )
    {
        /* Address to the section = beginning of file + accum. size */
        section_addr[i + 1] = (void*)((u32)data + total);
        
        /* Update accum. size */
        total += section_sizes[i];
    }
    
    /* Begin relocating */
    for( i = 0; i < ovl->relocate_count; i++ )
    {
        u32 w;
        u32 * tgt;
        int type;
        
        /* Grab next word */
        w = ovl->relocations[i];
        
        /* Set target base */
        tgt = section_addr[w >> 30];
        
        /* Unset? */
        if( !tgt )
        {
            /* Yep. Can't handle this */
            goto failed;
        }
        
        /* Finish the target address */
        tgt += (w & 0x00FFFFFF) / 4;
    
        /* What type is it? */
        type = (w >> 24) & 0x3F;
        
        /* Handle the type */
        switch( type )
        {
            /* Generic pointer */
            case R_PTR:
            {
              *tgt += offset;
            }
            break;
            
            /* Jump target */
            case R_J:
            {
              u32 new_tgt;
              u32 old_tgt;
              
              old_tgt = *tgt & 0x03FFFFFF;
              new_tgt = old_tgt + (offset / 4);;
              
              *tgt &= ~0x03FFFFFF;
              *tgt |= new_tgt;
            }
            break;
            
            /* LUI/IMMD part 1 */
            case R_PAIR1:
            {
              int reg;
              
              /* Get the register affected */
              reg = (*tgt >> 16) & 0x1F;
              
              /* Store address */
              pair_addrs[reg] = tgt;
              
              /* Start building value */
              pair_vals[reg] = (*tgt & 0xFFFF) << 16;
            }
            break;
            
            /* LUI/IMMD part 2 */
            case R_PAIR2:
            {
              int reg;
              u32 addr, hi, lo;
              short val;
              
              /* Get the register affected */
              reg = (*tgt >> 21) & 0x1F;
              
              /* Get the immediate value (always signed) */
              val = (short)(*tgt & 0xFFFF);
              
              /* Finish building the address */
              pair_vals[reg] += val;
              
              /* Relocate it */
              addr = pair_vals[reg] + offset;
              
              /* Set values */
              lo = addr & 0xFFFF;
              hi = (addr >> 16) + ((lo & 0x8000) ? 1 : 0);
              /*NOTE: since the immediate value is signed and can be negative,
                you need to add 1 to the high value if it is indeed < 0.      */
              
              /* Update addresses */
              *pair_addrs[reg] = (*pair_addrs[reg] & 0xFFFF0000) | hi;
              *tgt = (*tgt & 0xFFFF0000) | lo;
            }
            break;
            
            default:
             goto failed;
        }
        
        continue;
      
        /* Error during relocation */
      failed:
          
        /* Do not zero instruction
        *tgt = 0; */
    }
}

