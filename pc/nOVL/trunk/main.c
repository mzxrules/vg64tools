#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "novl.h"
#include "overlay.h"
#include "decoder.h"
#include "mesg.h"
#include "ansi.h"


/* ----------------------------------------------
   Constants
   ---------------------------------------------- */

enum nOVLopmode
{
    OP_NONE,
    OP_LIST_SECTIONS,
    OP_LIST_RELOCATIONS,
    OP_CONVERT,
    OP_DISASSEMBLE,
    OP_DISASSEMBLE_ALL
};


/* ----------------------------------------------
   Local variables
   ---------------------------------------------- */

/* Getopt format string */
static char * flags_fmt = "clrDdvho:A:?";

/* Command line arguments - flags */
static int Aflag, cflag, lflag, hflag, rflag, oflag, Dflag, dflag, vflag;

/* Command line arguments - values */
static uint32_t Aval;
static char * oval;
static int opmode;

/* Filenames */
static GList * filenames;


/* ----------------------------------------------
   Local functions
   ---------------------------------------------- */

/* Show usage */
static void
show_usage ( int argc, char ** argv )
{
    char * s = "[" ANSI_SET_FG_YELLOW "?" ANSI_RESET_DEFAULT "]";
    
    mk_mesg( s, "Application prototype:" );
    mk_mesg( s, "%s [-lrcDd] [-nhv] [-A address] [-o filename]", argv[0] );
    
    exit( EXIT_FAILURE );
}

/* Disassemble an actor file */
static void
disassemble ( char * filename, int all )
{
    int n, i, cnt;
    uint32_t w, addr;
    char buff[512];
    OVL * ovl;
    
    /* Load it */
    if( !(ovl = ovl_load(filename)) )
    {
        ERROR( "Couldn't load overlay file \"%s\": %s", filename, ovl_errmesg );
        exit( EXIT_FAILURE );
    }
    
    /* Disassemble everything? */
    if( all == 1 )
        cnt = 3;
    else
        cnt = 1;
    
    /* Set base address */
    addr = Aval;
    
    /* Start disassembly on a section */
    for( i = 0; i < cnt; i++ )
    {
        /* Header */
        printf( 
            "Disassembly of \"%s\": section %s\n",
            filename,
            ovl_section_names[i]
        );
        
        /* Begin reading & printing */
        for( n = 0; n < ovl->sections[i]->size; n += 4 )
        {
            /* Read word */
            w = *(uint32_t*)(ovl->sections[i]->data + n);
            w = g_ntohl( w ); /* swap */
            
            /* Disassemble it */
            mr4kd_disassemble( w, addr, buff );
            
            /* Print it */
            if( vflag )
                printf( "%08X: (%08X) %s\n", addr, w, buff );
            else
                printf( "%08X: %s\n", addr, buff );
            
            /* Update address */
            addr += 4;
        }
    }
    
    /* Finished */
    ovl_free( ovl );
}


/* List the relocations inside an overlay */
static void
list_relocations ( char * filename )
{
    int i;
    OVL * ovl;
    
    /* Load it */
    if( !(ovl = ovl_load(filename)) )
    {
        ERROR( "Couldn't load overlay file \"%s\": %s", filename, ovl_errmesg );
        exit( EXIT_FAILURE );
    }
    
    /* Header */
    printf( "Dump of relocations from \"%s\":\n", filename );
    printf( "ADDRESS     SECTION   REL TYPE        VALUE\n" );
    
    /* Display */
    for( i = 0; i < ovl->relocation_count; i++ )
    {
        int a;
        
        a = OVL_RELOC_GET_ABS_ADDR(ovl, ovl->relocations[i]);
        
        printf( 
            "0x%08X  %-8s  %-14s  0x%08X\n", 
            a + Aval,
            ovl_section_names[OVL_RELOC_GET_SEC(ovl->relocations[i])],
            novl_str_reloc_types[OVL_RELOC_GET_TYPE(ovl->relocations[i])],
            g_ntohl( *(uint32_t*)(ovl->data + a) )
        );
    }
    
    /* Done with overlay file */
    ovl_free( ovl );
    
    /* Spacing */
    printf( "\n\n" );
}

/* List the sections of an overlay */
static void
list_sections ( char * filename )
{
    int i;
    OVL * ovl;
    char size[64];
    
    /* Load it */
    if( !(ovl = ovl_load(filename)) )
    {
        ERROR( "Couldn't load overlay file \"%s\": %s", filename, ovl_errmesg );
        exit( EXIT_FAILURE );
    }
    
    /* Header */
    printf( "Dump of sections from \"%s\":\n", filename );
    printf( "NAME       ADDRESS        SIZE\n" );
    
    /* Print them */
    for( i = 0; ovl->sections[i]; i++ )
    {
        if( hflag )
            format_value( size, ovl->sections[i]->size );
        else
            snprintf( size, sizeof(size), "%i", ovl->sections[i]->size );
        
        printf( 
            "%-10s 0x%08X     %s\n", 
            ovl_section_names[i], 
            Aval + ovl->sections[i]->addr,
            size
        );
    }
    
    /* Done with overlay file */
    ovl_free( ovl );
    
    /* Spacing */
    printf( "\n\n" );
}

/* Convert an elf to an overlay */
static void
convert_elf ( char * filename )
{
    /* We need the -o flag */
    if( !oflag )
    {
        ERROR( "Please specify an output file with -o." );
        exit( EXIT_FAILURE );
    }
    
    /* We need the -A flag */
    if( !Aflag )
    {
        ERROR( "Please specify a target address with -A." );
        exit( EXIT_FAILURE );
    }
    
    novl_conv( Aval, filename, oval );
}


/* Check if an opmode has already been set... */
static void
check_opmode ( void )
{
    if( opmode )
    {
        ERROR( "You can only specify one of the -clr options!" );
        exit( EXIT_FAILURE );
    }
}

/* Process command line arguments */
static void
args_process ( int argc, char ** argv )
{
    int c, i;
    
    /* Loop through arguments */
    while( (c = getopt(argc, argv, flags_fmt)) != -1 )
    {
        /* Handle... */
        switch( c )
        {
            /* List sections */
            case 'l':
            {
              check_opmode();
              lflag = 1;
              opmode = OP_LIST_SECTIONS;
              settings.mode = opmode;
              
              
              MESG( "List sections mode." );
            }
            break;
            
            /* List relocations */
            case 'r':
            {
              check_opmode();
              rflag = 1;
              opmode = OP_LIST_RELOCATIONS;
              settings.mode = opmode;
              
              MESG( "List relocations mode." );
            }
            break;
            
            /* Convert mode */
            case 'c':
            {
              check_opmode();
              cflag = 1;
              opmode = OP_CONVERT;
              settings.mode = opmode;
              
              MESG( "ELF -> overlay convert mode." );
            }
            break;
            
            /* Disassemble text */
            case 'd':
            {
              dflag = 1;
              opmode = OP_DISASSEMBLE;
              settings.mode = opmode;
              
              MESG( "Disassembly mode." );
            }
            break;
            
            /* Disassemble all */
            case 'D':
            {
              Dflag = 1;
              opmode = OP_DISASSEMBLE_ALL;
              settings.mode = opmode;
              
              MESG( "Disassemble ALL mode." );
            }
            break;
            
            
            /* Actor base address */
            case 'A':
            {
              sscanf( optarg, "%X", &Aval );
              Aflag = 1;
              settings.ovl_base = Aval;
              
              MESG( "Overlay base address set to 0x%08X.", Aval );
            }
            break;
            
            /* Output file (for converter) */
            case 'o':
            {
              oval = optarg;
              oflag = 1;
              
              MESG( "Writing overlay to \"%s\".", oval );
            }
            break;
            
            /* Make int values human readable */
            case 'h':
            {
              hflag = 1;
              settings.human_readable = 1;
              
              MESG( "Printing human readable values." );
            }
            break;
            
            /* Display instructions raw */
            case 'v':
            {
              vflag = 1;
              
              MESG( "Displaying raw instructions in disassembly output." );
            }
            break;
            
            case '?': default:
             show_usage( argc, argv );
             exit( EXIT_FAILURE );
        }
    }
    
    /* No filename arguments? */
    if( optind == argc )
    {
        ERROR( "Please provide at least one filename as an argument." );
        exit( EXIT_FAILURE );
    }
    
    /* The rest of the arguments are filenames */
    for( i = optind; i < argc; i++ )
    {
        /* Check... */
        if( opmode == OP_CONVERT && i == optind + 1 )
        {
            ERROR( "Only one filename required for this mode." );
            exit( EXIT_FAILURE );
        }
        
        /* Append it to our list */
        filenames = g_list_append( filenames, argv[i] );
    }
}




int
main ( int argc, char ** argv )
{
    GList * s;
    
    /* Header */
    MESG( 
        ANSI_SET_FG_WHITE_BOLD 
        NOVL_NAME 
        ANSI_RESET_DEFAULT
        " "
        NOVL_VERSION_STR
        " by "
        NOVL_AUTHOR
    );
    MESG(
        "Built: "
        __DATE__ " " __TIME__
    );
    
    /* Process the arguments */
    args_process( argc, argv );
    
    /* Take action! */
    switch( opmode )
    {
        case OP_LIST_RELOCATIONS:
        {
           for( s = filenames; s; s = s->next )
               list_relocations( s->data );
        }
        break;
        
        case OP_LIST_SECTIONS:
        {
           for( s = filenames; s; s = s->next )
               list_sections( s->data );
        }
        break;
        
        case OP_CONVERT:
        {
          /* First filename only! */
          convert_elf( filenames->data );
        }
        break;
        
        case OP_DISASSEMBLE:
        {
           for( s = filenames; s; s = s->next )
               disassemble( s->data, 0 );
        }
        break;
        
        case OP_DISASSEMBLE_ALL:
        {
           for( s = filenames; s; s = s->next )
               disassemble( s->data, 1 );
        }
        break;
        
        
        default:
         show_usage( argc, argv );
         return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

