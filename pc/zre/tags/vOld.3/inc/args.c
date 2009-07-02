/*********************************
* COMMAND LINE ARGUMENTS HANDLER *
*********************************/
#include <stdio.h>
#include "../zre.h"
#include "msg.h"

/*
   For __MSG_* used in here, see msg.h
*/

int zre_handle_arguments ( int argc, char **argv ){
	
	/* Variables */
	int i;
	
	/* Check that there are actually args */
	if(argc == 1)
		return 0;
	
	/* Loop through each arg */
	for(i = 1; i < argc; i++){
		
		/* Single letter */
		if(argv[i][0]=='-'&&argv[i][1]!='-') switch(argv[i][1]){
			
			/* Yes to all */
			case 'y':
				conf.yta = true;
				MESSAGE(__MSG_YTA);
			break;
			
			/* Silent mode */
			case 'S':
				conf.silent = true;
			break;
			
			/* Strip filename prefixes */
			case 's':
				conf.strip = true;
				MESSAGE(__MSG_STRIP);
			break;
			
			/* Debug mode */
			case 'd':
				conf.debug = true;
				MESSAGE(__MSG_DBG);
			break;
			
			/* Output directory */
			case 'o':
				if(argc > i+1){
					conf.odir = argv[(i++)+1];
					MESSAGE(__MSG_ODIR,conf.odir);
				}else{
					/* None given? */
					MESSAGE(__MSG_ODIRNE);
				}
			break;
			
			/* File ID; relative to file table */
			case 'L':
				conf.fid = 1;
				MESSAGE(__MSG_FID1);
			break;
			
			/* File ID; relative to files extracted */
			case 'l':
				conf.fid = 2;
				MESSAGE(__MSG_FID2);
			break;
			
			/* Do not write to disk */
			case 'n':
				conf.nwrite = true;
				MESSAGE(__MSG_NWRT);
			break;
			
			/* Do not get filenames */
			case 'u':
				conf.skip_names = true;
				MESSAGE(__MSG_NNAMES);
			break;
			
			/* UoT mode: supress all messages and errors */
			case 'U':
				conf.silent = true;
				conf.uot = true;
			break;
			
			/* Offsets in filename */
			case 'O':
				conf.offsets = argv[i][2]-'0';
				MESSAGE(__MSG_OTYPE,conf.offsets);
			break;
			
			/* Do not detect tables at all */
			case 't':
				conf.notable = true;
				MESSAGE(__MSG_NTABLE);
			break;
			
			/* No scene table */
			case 'T':
				conf.noscene = true;
				MESSAGE(__MSG_NSCENE);
			break;
			
			/* No actor table */
			case 'A':
				conf.noactor = true;
				MESSAGE(__MSG_NACTOR);
			break;
			
			/* Notify user of error */
			default:
				MESSAGE(__MSG_UFLAG,argv[i][1]);
		}
		
			
		/* Check for credits */
		else if(!strcmp(argv[i],"--credits")) {
			zre_print_credits();
		}
		
		/* Check for help */
		else if(!strcmp(argv[i],"--help")) {
			zre_print_help();
		}
		
		/* Check for filename */
		else { /* use global file handle */
			if((fhandle = fopen(argv[i],"rb"))){
				filename = argv[i];
				MESSAGE(__MSG_IROM,filename);
			}else{
				MESSAGE(__MSG_UARG,argv[i]);
			}
		}
	}
	
	return (!filename ? 0 : 1);
}
