/*********************
* VARIOUS PROCEDURES *
*********************/
#include <stdio.h>
#include <dirent.h>
#include "../zre.h"

void zre_proc_get_filename ( void ){
	
	/* Vars */
	char tmpbuff[512];
	int len;
	printf("No filename given via arguments!\n");
	
	/* Notify */
	while(!fhandle){
		printf("Please enter a filename or 'q' to quit:\n");
		READTOSTR(tmpbuff,sizeof(tmpbuff));
		if(toupper(tmpbuff[0])=='Q'&&!tmpbuff[1])
			exit(0);
		else
			fhandle = fopen(tmpbuff,"rb");
	}
	
	/* Set aside memory for new filename */
	filename = malloc((len = strlen(tmpbuff)));
	strncpy(filename,tmpbuff,len);
}

void zre_proc_prepare_name ( void ){
	/* Variables */
	char *p = output_filename, temp[64];
	
	/* Append output directory */
	p += sprintf(p,"%s/", conf.odir);
	
	/* File IDs in name */
	switch(conf.fid){
		case 1:
		p+=sprintf(p,"%04u - ",ZFCPOS(fsh));
		break;
		
		case 2:
		p+=sprintf(p,"%04u - ",stats.files_extracted);
		break;
	}
	
	if(!conf.skip_names){
		if(!conf.strip)
			p+=sprintf(p,"%s",nth->cur);
		else {
			strcpy(temp, nth->cur);
			str_replace("object_","",temp);
			str_replace("ovl_","",temp);
			str_replace("_scene","",temp);
			str_replace("_room","",temp);
			p+=sprintf(p,"%s",temp);
		}
			
		switch(conf.offsets){
			case 1:
			p+=sprintf(p," [%08X - %08X]",ZF1START(fsh),ZF1END(fsh));
			break;
			
			case 2:
			p+=sprintf(p," [%08X - %08X]",ZF2START(fsh),ZF2END(fsh));
			break;
			
			case 3:
			p+=sprintf(p," [%08X - %08X] [%08X - %08X]",
			ZF1START(fsh),ZF1END(fsh),ZF2START(fsh),ZF2END(fsh));
			break;
		}
	}else{
		p+=sprintf(p,"%08X - %08X",ZF1START(fsh),ZF1END(fsh));
	}
	p+=sprintf(p,".%s",string_filetype(&fbuff));
			
	DEBUG(printf("%s | %.2fkb\n",output_filename,(float)fbuff.length/1024.0));
}

int zre_proc_offsetcheck ( void ){
	
	if(!z64fs_file_exists(fsh))
		return 0;
	else if(ZF2START(fsh) > rfilesize || ZF2END(fsh) > rfilesize)
		return 0;
	else if(ZF1START(fsh) > ZF1END(fsh) || ZF2START(fsh) > ZF2END(fsh))
		return 0;
	else
		return 1;
}

int zre_proc_get_filetype ( void ){
	if(!conf.skip_names)
		return zd_detect_name_main(nth->cur);
	else
		return zd_detect_main(&fbuff);
}

void zre_proc_create_out ( void ){
	char syscmd[512]; DIR *h;
	if(!(h = opendir(conf.odir))){
		sprintf(syscmd,"mkdir \"%s\"", conf.odir);
		system(syscmd);
	}else closedir(h);
}
static u8 tconf;
int zre_proc_handle_tables ( void ){
	
	/* Are we allowed? */
	if(conf.notable)
		return 0;
	
	/* Status; unless we've reached a zasm block, do nothing */
	if(!tconf && fbuff.type == type_zasm)
		tconf = 1;
	
	/* Call relevant functions */
	if(tconf) /* check that we have reached code */
		if(conf.noscene||!zre_scene_main()) /* zscene/zmap */
			if(conf.noactor||!zre_actor_main()) /* zactor */
				return 0;
	return 1;
}
