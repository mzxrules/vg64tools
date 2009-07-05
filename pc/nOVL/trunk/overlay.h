#ifndef __OVERLAY_H__
#define __OVERLAY_H__

#include <elf.h>
#include <stdint.h>


/* ----------------------------------------------
   Macros & constants
   ---------------------------------------------- */

#define OVL_RELOC_GET_ADDR(r)           ((r) & 0x00FFFFFF)
#define OVL_RELOC_GET_SEC(r)            (((r) >> 30) - 1)
#define OVL_RELOC_GET_TYPE(r)           (((r) >> 24) & 0x3F)

#define OVL_RELOC_GET_ABS_ADDR(o,r)                 \
(                                                   \
    (o)->sections[OVL_RELOC_GET_SEC(r)]->addr +     \
    OVL_RELOC_GET_ADDR(r)                           \
)

enum OvlSections
{
    OVL_S_TEXT,
    OVL_S_DATA,
    OVL_S_RODATA,
    OVL_S_BSS,
    OVL_S_COUNT
};
   

/* ----------------------------------------------
   Data types
   ---------------------------------------------- */

/* Raw OVL header */
struct ovl_header_t
{
    uint32_t sizes[OVL_S_COUNT];
    uint32_t relocation_count;
};
   
/* A container for a section */
struct ovl_section_t
{
    uint32_t  addr;
    int       size;
    uint8_t * data;
};

/* OVL file context */
struct ovl_t
{
    /* NULL terminated list of sections */
    struct ovl_section_t ** sections;
    
    /* Amount of relocations */
    int relocation_count;
    
    /* Pointer to data */
    uint8_t * data;
    
    /* Length */
    int filesize;
    
    /* Relocation words */
    uint32_t * relocations;
};

/* Shorthand */
typedef struct ovl_t        OVL;
typedef struct ovl_header_t OVLHead;


/* ----------------------------------------------
   Variable declarations
   ---------------------------------------------- */

extern char * ovl_errmesg;
extern char * ovl_section_names[];


/* ----------------------------------------------
   Function declarations
   ---------------------------------------------- */

extern OVL     * ovl_load       ( char * );
extern void      ovl_free       ( OVL * );
extern int       ovl_set_error  ( char *, ... );
extern uint8_t * ovl_get_header ( OVL *, OVLHead * );


#endif /* __OVERLAY_H__ */

