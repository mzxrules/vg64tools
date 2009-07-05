#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <elf.h>
#include <libelf.h>
#include <gelf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "novl.h"
#include "overlay.h"
#include "mesg.h"


/* This is an ugly hack! */
uint32_t bin_min;
uint32_t bin_max;


/* ----------------------------------------------
   Local variables 
   ---------------------------------------------- */

static FILE      * ovl_out;
static uint32_t    elf_ep;
static uint8_t     memory[4 * 1024 * 1024];
static uint32_t    starts[OVL_S_COUNT];
static uint32_t    sizes[OVL_S_COUNT];
static int         elf_fd;
static Elf       * elf;
static GElf_Ehdr   elf_head;
static int         offset;


static struct 
{
    char * marker;
    uint32_t * start;
    uint32_t * size;
}
spec[] =
{
    { ".text",   &starts[OVL_S_TEXT],   &sizes[OVL_S_TEXT]   },
    { ".data",   &starts[OVL_S_DATA],   &sizes[OVL_S_DATA]   },
    { ".rodata", &starts[OVL_S_RODATA], &sizes[OVL_S_RODATA] },
    { ".bss",    &starts[OVL_S_BSS],    &sizes[OVL_S_BSS]    },
    { NULL }
};


/* ----------------------------------------------
   Local functions 
   ---------------------------------------------- */

static int
valid_sec ( char * s )
{
    int i;
    
    for( i = 0; spec[i].marker; i++ )
    {
        if( !strncmp(s, spec[i].marker, strlen(spec[i].marker) - 1) )
            return i;
    }
    
    return -1;
}


/* ----------------------------------------------
   Global functions 
   ---------------------------------------------- */

/* Convert an ELF file to a Nintendo overlay */
void
novl_conv ( uint32_t tgt_addr, char * in, char * out )
{
    Elf_Kind kind;
    Elf_Scn * section;
    GElf_Shdr sh_header;
    size_t sh_strcount;
    GElf_Rel rel;
    GList * seek;
    uint32_t header_offset;
    struct ovl_header_t new_head;
    GList * ninty_relocs;
    int ninty_count;
    char * name;
    Elf_Data * data;
    int i, n, v;
    uint32_t tmp;
    uint32_t greatest;
    
    ninty_relocs = NULL;
    ninty_count = 0;
    v = 0;
    greatest = 0;
    
    /* Open the ELF file for reading */
    if( (elf_fd = open(in, O_RDONLY, 0)) < 0 )
    {
        ERROR( "open() failed: %s", strerror(errno) );
        exit( EXIT_FAILURE );
    }
    
    /* Set ELF version */
    elf_version( EV_CURRENT );
    
    /* Create libelf context */
    if( !(elf = elf_begin(elf_fd, ELF_C_READ, NULL)) )
    {
        ERROR( "elf_begin() failed: %s", elf_errmsg(-1) );
        exit( EXIT_FAILURE );
    }
    
    /* Get kind of file */
    switch( (kind = elf_kind(elf)) )
    {
        case ELF_K_AR:
         ERROR( "ar(1) archive provided -- elf files only, please!" );
         exit( EXIT_FAILURE );
        break;
        
        case ELF_K_ELF: break;
        
        default:
         ERROR( "Unsupported input format." );
         exit( EXIT_FAILURE );
    }
    
    /* Read header */
    if( !gelf_getehdr(elf, &elf_head) )
    {
        ERROR( "gelf_getehdr() failed: %s", elf_errmsg(-1) );
        exit( EXIT_FAILURE );
    }
    
    /* CHeck machine arch */
    if( elf_head.e_machine != EM_MIPS )
    {
        ERROR(
            "This program is for MIPS binaries only, silly!"
        );
        exit( EXIT_FAILURE );
    }
    
    /* Set entry point */
    elf_ep = elf_head.e_entry;
    bin_min = elf_ep;
    
    /* Notice */
    MESG( "\"%s\": valid MIPS ELF file.", in );
    MESG( "Entry point: 0x%08X. Translating to 0x%08X.", elf_ep, tgt_addr );
    
    /* Set offset */
    offset = tgt_addr - elf_ep;
    
    /* Output file */
    if( !(ovl_out = fopen(out, "wb")) )
    {
        ERROR( 
            "Can't open \"%s\" for writing: %s",
            out, strerror(errno)
        );
        exit( EXIT_FAILURE );
    }
  
    
    
    /*
    **
    ** Start loading the file into memory
    **
    */
    
    /* Set up */
    elf_getshstrndx( elf, &sh_strcount );
    section = NULL;
    
    /* Loop through sections; find loadable ones */
    while( (section = elf_nextscn(elf, section)) )
    {
        int id;
        
        /* Get the header */
        gelf_getshdr( section, &sh_header );
        
        /* Get name */
        name = elf_strptr( elf, sh_strcount, sh_header.sh_name );
        
        /* Is this one we want? */
        if( (id = valid_sec(name)) == -1 )
        {
            /* No */
            continue;
        }
        
        /* Set the start addr & size */
        if( !*spec[id].start )
            *spec[id].start = sh_header.sh_addr;
        *spec[id].size += (sh_header.sh_size - (sh_header.sh_size % 8) + 8);
        
        /* Can we load this into memory? */
        if( sh_header.sh_type == SHT_PROGBITS )
        {
            int n;
            
            /* Keep tabs on last boundry */
            if( sh_header.sh_size + sh_header.sh_addr > greatest )
                greatest = sh_header.sh_size + sh_header.sh_addr;
            
            data = NULL;
            
            /* Sanity check... */
            if( (sh_header.sh_addr + sh_header.sh_size) - elf_ep > sizeof(memory) )
            {
                ERROR( "Error - memory bounds reached." );
                exit( EXIT_FAILURE );
            }
            
            /* Load it */
            for( n = 0; n < sh_header.sh_size && (data = elf_getdata(section, data)); n += data->d_size )
            {
                memcpy( memory + (sh_header.sh_addr - elf_ep), data->d_buf, data->d_size );
            }
            
            /**/ DEBUG( "Copied '%s' (%i bytes) to 0x%08X.", name, (int)sh_header.sh_size, (int)sh_header.sh_addr );
        }
    }
    
    bin_max = greatest + sizes[OVL_S_BSS];
    
    /* Sections should've loaded now */
    #ifdef NOVL_DEBUG
     for( i = 0; i < OVL_S_COUNT; i++ )
     {
         DEBUG( "%-8s 0x%08X %ib", spec[i].marker, *spec[i].start, *spec[i].size );
     }
    #endif
    
    
    
    /*
    **
    ** Relocate the file
    **
    */
    
    /* Step through section list once more */
    elf_getshstrndx( elf, &sh_strcount );
    section = NULL;
    while( (section = elf_nextscn(elf, section)) )
    {
        int id;
        
        /* Get the header */
        gelf_getshdr( section, &sh_header );
        
        /* Get name */
        name = elf_strptr( elf, sh_strcount, sh_header.sh_name );
        
        /* Relocation header? */
        if( strncmp(".rel.", name, 4) )
            continue;
        
        /* Is this one we want? */
        if( (id = valid_sec(name+4)) == -1 )
        {
            /* No */
            continue;
        }
        
        /* We want this */
        DEBUG( "Processing relocation entries from '%s'.", name ) ;
        
        data = NULL;
        
        /* Get section data */
        for( n = 0; n < sh_header.sh_size && (data = elf_getdata(section, data)); n += data->d_size )
        {
            /* Get relocations */
            for( i = 0; gelf_getrel(data, i, &rel); i++ )
            {
                uint32_t off, nr;
                int v;
                
                /* Calculate offset */
                off = (uint32_t)rel.r_offset - elf_ep;
                
                /* Skip this relocation? */
                if( ((rel.r_info >> 32) & 0) )
                {
                    /* Yeah, address isn't under our jurisdiction */
                    /**/DEBUG( "Hopping over relocation entry for 0x%08X.", (uint32_t)rel.r_offset );
                    continue;
                }
                
                /* Relocate! */
                v = novl_reloc_do( (uint32_t*)(&memory[off]), (int)rel.r_offset, (int)rel.r_info, offset );
                
                /* Check result */
                if( !v )
                {
                    /* Whaat? */
                    ERROR( "Relocation type %s has no registered handler. Abort.", novl_str_reloc((int)rel.r_info) );
                    DEBUG( "%i,%i", (int)rel.r_offset, (int)rel.r_info );
                    exit( EXIT_FAILURE );
                }
                
                /* Generate a nintendo relocation */
                nr = novl_reloc_mk(id + 1, (int)rel.r_offset - starts[id], (int)rel.r_info);
                ninty_relocs = g_list_append( ninty_relocs, GUINT_TO_POINTER(nr) );
                ninty_count++;
            }
        }
    }
    
    /*
     Okay! So at this point, the binary has been relocated, and the Nintendo-
     friendly relocation entries generated.
     Now all we have to do is generate the header and write the data to disk
    */
    
    /* Copy sizes */
    memcpy( new_head.sizes, sizes, sizeof(new_head.sizes) );
    new_head.relocation_count = ninty_count;
    
    /* Swap... */
    for( i = 0; i < sizeof(new_head)/4; i++ )
        ((uint32_t*)&new_head)[i] = g_htonl(((uint32_t*)&new_head)[i]);
    
    /* Write it */
    header_offset = greatest - elf_ep;
    fseek( ovl_out, header_offset, SEEK_SET );
    v = fwrite( &new_head, 1, sizeof(new_head), ovl_out );
    MESG( "Wrote section descriptions (%ib).", v );
    
    /* Write the relocation entries */
    for( seek = ninty_relocs, v = 0; seek; seek = seek->next )
    {
        uint32_t w;
        
        w = GPOINTER_TO_UINT(seek->data);
        w = g_htonl( w );
        
        v += fwrite( &w, 1, sizeof(w), ovl_out );
    }
    MESG( "Wrote relocation entries (%ib).", v );
    
    /* Write offset from here to header */
    tmp = g_htonl( ftell(ovl_out) - header_offset + 4 );
    v = fwrite( &tmp, 1, sizeof(tmp), ovl_out );
    MESG( "Finalized footer (%ib).", v );
    
    /* Write the data */
    fseek( ovl_out, 0, SEEK_SET );
    v = fwrite( memory, 1, header_offset, ovl_out );
    fclose( ovl_out );
    MESG( "Wrote binary data (%ib).", v );
    
    /* Free up some memory */
    g_list_free( ninty_relocs );
}

