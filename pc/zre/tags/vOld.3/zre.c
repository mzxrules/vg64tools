/***************************
* ZELDA RESOURCE EXTRACTOR *
***************************/

/*
	ZZT32 (zz@64.vg)
	~~~~~~~~~~~~~~~~
	http://www.64.vg

	This is free public domain software. You may modify 
	and redistribute it as long as the original credits
	remain intact. If in doubt, please contact the author.
*/

/* Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/* Headers pertaining to z64l */
#include "z64l/z64lib.h"

/* Headers pertaining to ZRE */
#include "zre.h"
#include "inc/args.c"
#include "inc/procedures.c"
#include "inc/rom.c"
#include "inc/progbar.c"
#include "inc/functions.c"
#include "inc/scenet.c"
#include "inc/actort.c"
#include "inc/termio.c"

/* Configuration/shared variables */
struct config conf;
struct statistics stats;
char *filename = NULL;
u32 rfilesize = 0, rident = __GAME_UNK;
FILE *fhandle = NULL;
char output_filename[1024];
Z64FS *fsh; /* filesystem handle */
Z64FB fbuff; /* file buffer */
Z64NT *nth; /* name table handle */

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

int main ( int argc, char **argv ){
	
	/* Variables */
	u32 i, nent, decamt;
	u8 *temp;
	FILE *out;
	clock_t s,e;
	
	/* Progress bar variables */
	u32 pbwrote = 0, pbinterval = 80, pbcnt = 0;
	
	/* Display application header */
	zre_print_header();
	
	/* Take care of any would-be arguments */
	if(!zre_handle_arguments(argc, argv)){
		
		/* Oh? No filename/arguments. Ask for filename */
		zre_proc_get_filename();
	}
	
	/* Check input ROM; see rom.c for code */
	zre_rom_check(); /* handles byteswapping/N64 ROM integrity checking */
	
	/* Get ROM filesize */
	fseek(fhandle, 0, SEEK_END);
	rfilesize = ftell(fhandle); /* subroutines will seek back to 0 */
	
	/* Set output directory; see zre.h for default */
	if(!conf.odir){
		conf.odir=malloc(sizeof(__ODIR_DEFAULT));
		strcpy(conf.odir,__ODIR_DEFAULT);
	}
	
	/* Create output directory */
	zre_proc_create_out();
	
	/* filename should now be valid */
	if(!(fsh = z64fs_init(filename))){
		ERROR("No filesystem was found in the file you provided. "
		"Either the ROM corrupted or\nit isn't a Zelda 64 ROM. ");
	}
	
	/* Game ident */
	rident = zre_rom_ident_name();
	if(rident != __GAME_UNK){
		MESSAGE("\nGame build found: ");
		zre_rom_print_name(rident);
		MESSAGE(". Searching for scene table accordingly.");
	}
	
	/* Filesystem found, display some info */
	decamt = z64fs_calc_size_decompressed(fsh);
	DEBUGA(
		/* Stuff to display if debug mode is on*/
		z64fs_dump_handle(fsh),
		
		/* stuff to display if not */
		MESSAGE("\nFilesystem found, %u files in total. "
		"%.2fMB of space required to extract.\n",z64fs_num_entries(fsh),
		(float)decamt/1024.0/1024.0)
	);
	
	/* Check for name table */
	if(!(nth = z64nt_init(filename))){
		MESSAGE("No name table found.\n");
		conf.skip_names = true;
	} else {
		/* Found! */
		nent = z64nt_count_entries(nth);
		MESSAGE("Name table found at: $%08X -> $%08X; %lu entries.\n",
		__NAME_TABLE_START,__NAME_TABLE_END,nent);
		
		/* Another quick check... */
		if(nent != z64fs_num_entries(fsh)){
			MESSAGE("Amount of files and amount of filenames don't "
			"match -- skipping filename extraction.\n");
			z64nt_close(nth);
			conf.skip_names = true;
		}
	}
	
	/* Start timer */
	s = clock();
	
	/* Main loop */
	for( i=0; i < z64fs_num_entries(fsh); i++ ){
		
		/* Read next set of offsets */
		z64fs_read_next(fsh);
		
		/* Check for invalid entries */
		if(!zre_proc_offsetcheck()){
			DEBUGA(
				/* Display some info about the offsets */
				FMESSAGE("Offsets did not pass check:\n");
				z64fs_dump_file_info(fsh); goto eol
				,
				/* Skip */
				goto eol
			);
		}
		
		/* Read file into RAM */
		fbuff.data = malloc((fbuff.length = Z2FSIZE(fsh)));
		fseek(fhandle, ZF2START(fsh), SEEK_SET);
		fread(fbuff.data, 1, fbuff.length, fhandle);
		
		/* Check if we need to decompress */
		if(z64fs_is_compressed(fsh)&&!strncmp(fbuff.data,"Yaz0",4)){
			
			/* Set aside some ram for decompression */
			if(!(temp = malloc(Z1FSIZE(fsh)))){
				ERROR("Unable to allocate %.2fkb needed for Yaz0 block decompression! ",
				(float)Z1FSIZE(fsh)/1024.0);
			}
			
			/* Do the decompression */
			decode(fbuff.data+16, temp, Z1FSIZE(fsh));
		
			/* Free original */
			free(fbuff.data);
			
			/* Allocate more memory */
			fbuff.data = malloc((fbuff.length=Z1FSIZE(fsh)));
			memcpy(fbuff.data, temp, fbuff.length);
			free(temp);
		}
		
		/* Identify */
		fbuff.type = zre_proc_get_filetype();
			
		/* Second opinion! */
		zre_proc_handle_tables();
		
		/* Prepare output filename; see procedures.c */
		zre_proc_prepare_name();
		
		/* Write file to disk; see zre.h for macro */
		WRITE_OUTPUT_FILE(output_filename, out, fbuff.data, fbuff.length);
		
		/* Free resources */
		free(fbuff.data);
		
		/* Update stats */
		stats.files_extracted++;
		
		/* End of loop */
		eol:
		
		/* Update amount processed */
		stats.amt_processed += Z1FSIZE(fsh);
			
		/* Take care of progress bar */
		if(pbcnt == pbinterval){
			erase_previous(pbwrote);
			DRAWBAR(DEFAULT_BAR_LENGTH,0,decamt,
			stats.amt_processed,2,3,pbwrote);
			pbcnt = 0;
		}else{ pbcnt++; }
		
		/* read next name table entry if applicable */
		ZNT_READ_NEXT(nth);
		continue;
	}
	
	/* End clock */
	e = clock();
	
	/* ~~~~ Finished! ~~~~ */
	
	/* Last progress bar update */
	erase_previous(pbwrote);
	DRAWBAR(DEFAULT_BAR_LENGTH,0,decamt,stats.amt_processed,2,3,pbwrote);
	
	/* Closing message */
	MESSAGE("\n\nFinished! %u/%u files extracted. Time taken: %.2f seconds.\n",
	stats.files_extracted,z64fs_num_entries(fsh),(double)(e-s)/CLOCKS_PER_SEC); 
	FMESSAGE("\n");
}
