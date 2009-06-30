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

/*
  Header structure -- 
  Overlay header describing the section sizes, the amount of relocations, and
  the relocations themselves.
*/
struct ovl_header
{
    uint32_t sizes[S_COUNT];
    int relocate_count;
    uint32_t relocations[];
};


/* ----------------------------------------------
   Global functions
   ---------------------------------------------- */

void
z_ovl_adapt ( void * data, struct ovl_header * ovl, void * ovl_base )
{
    int i, total;
    uint32_t * section_sizes;
    void * section_addr[S_COUNT + 1];
    uint32_t pair_vals[32];
    uint32_t * pair_addrs[32];
    
    /* First one is initialized to zero */
    section_addr[0] = NULL;
    
    /* Set pointer to section sizes... */
    section_sizes = ovl->sizes;
    
    /* Set the section addresses */
    for( i = 0, total = 0; i < S_COUNT; i++ )
    {
        /* Address to the section = beginning of file + accum. size */
        section_addr[i + 1] = data + total;
        
        /* Update accum. size */
        total += section_sizes[i];
    }
    
    /* Begin relocating */
    for( i = 0; i < ovl->relocate_count; i++ )
    {
        uint32_t w;
        uint32_t * tgt;
        int type, v;
        
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
              *tgt = (uint32_t)data + (*tgt - (uint32_t)ovl_base);
            }
            break;
            
            /* Jump target */
            case R_J:
            {
              uint32_t new_tgt;
              
              new_tgt = (((uint32_t)data & 0x00FFFFFF) >> 2) + ((*tgt & 0x03FFFFFF) - (((uint32_t)ovl_base & 0x00FFFFFF) >> 2));
              
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
              uint32_t addr, hi, lo;
              short val;
              
              /* Get the register affected */
              reg = (*tgt >> 21) & 0x1F;
              
              /* Get the immediate value (always signed) */
              val = (short)(*tgt & 0xFFFF);
              
              /* Finish building the address */
              pair_vals[reg] += val;
              
              /* Relocate it */
              addr = (uint32_t)data + (pair_vals[reg] - (uint32_t)ovl_base);
              
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
          
        /* Zero instruction */
        *tgt = 0;
    }
}

