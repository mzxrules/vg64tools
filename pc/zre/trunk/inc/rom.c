/****************************
* ROM BYTESWAPPING/HANDLING *
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../zre.h"
#include "rom.h"

/*
	ROM Byteswap/Integrity Checking
*/
void zre_rom_check ( void ){
	
	/* Variables */
	u32 endian, crc[2], i;
	u8 *rom_head = malloc(CHECKSUM_START+CHECKSUM_LENGTH);
	
	/* Read first */
	fseek(fhandle, 0, SEEK_SET);
	fread(rom_head, 1, CHECKSUM_START+CHECKSUM_LENGTH, fhandle);
	endian = BYTES2LONG(rom_head);
	
	/* Display ROM identifier */
	DEBUG(FMESSAGE("ROM identifier is: $%08X\n",endian));
	
	/* Switch */
	switch(endian){
		
		/* Big endian, no swapping required */
		case __ENDIAN_BIG:
			goto crc;
		break;
		
		/* Byteswapping required */
		case __ENDIAN_SMALL: 
		case __ENDIAN_V64:
			zre_rom_swap();
		break;
		
		/* No idea? */
		default:
			ERROR("ROM is corrupt or in unknown endian. ROM's "
			"identifier is: $%08X.\n", endian);
	}
	
	/* Set up CRC stuff */
	crc: gen_table();
	if(!N64CalcCRC(crc,rom_head)&&(crc[0]!=BYTES2LONG(rom_head+N64_CRC1)||crc[1]!=BYTES2LONG(rom_head+N64_CRC2))){
		
		/* Notify */
		MESSAGE("Current CRCs are incorrect: $%08X - $%08X.\n",
		BYTES2LONG(rom_head+N64_CRC1),BYTES2LONG(rom_head+N64_CRC2));
		
		/* Reopen file for writing */
		fclose(fhandle);
		fhandle = fopen(filename,"rb+");
		
		/* Fix */
		fseek(fhandle, N64_CRC1, SEEK_SET);
		for( i = 0; i < 8; i++ ) /* write two ints to disk */
			fputc(((crc[i >> 2] >> ((3 - i & 0x3) << 0x3)) & 0xff),fhandle);
		
		/* Close handle */
		fclose(fhandle);
		fhandle = fopen(filename,"rb");
		
		/* Notify */
		MESSAGE("Calculated and wrote new CRCs: $%08X - $%08X.\n",crc[0],crc[1]);
	}
	free(rom_head);
}

/*
	Identify game name (OOT or MM)
*/
int zre_rom_ident_name ( void ){
	
	/* Vars */
	char buff[64];
	
	/* Fill buff */
	fseek(fhandle, 0, SEEK_SET);
	fread(buff,1,sizeof(buff),fhandle);
	
	/* Check! */
	#define B (buff+0x20)
	if(!strncmp(__NAME_OOT1, B, sizeof(__NAME_OOT1)-1) || !strncmp(__NAME_OOT2, B, sizeof(__NAME_OOT2)-1))
		return __GAME_OOT;
	else if( !strncmp(__NAME_MM1, B, sizeof(__NAME_MM1)-1) ||
		 !strncmp(__NAME_MM2, B, sizeof(__NAME_MM2)-1) ||
	 	 !strncmp(__NAME_MM3, B, sizeof(__NAME_MM3)-1) )
		return __GAME_MM;
	else
		return __GAME_UNK;
}

/*
	ROM Byteswapper
	~~~~~~~~~~~~~~~
	This will only swap TO big endian, nothing else.
*/

void zre_rom_swap ( void ){
	
	/* easier for me */
	#define HA fhandle
	
	/* Variables */
	register u32 i;
	register u8 *buff;
	u8 buff2[16]; 
	u32 filesize;
	clock_t s,e;
	
	/* Read ROM */
	fseek(HA,0,SEEK_END);
	filesize = ftell(HA);
	fseek(HA,0,SEEK_SET);
	if(!(buff = malloc(filesize)))
		ERROR("Unable to allocate %.2fMbytes required for byteswapping "
		"ROM. ",(float)filesize/1024.0/1024.0);
	fread(buff,1,filesize,HA);
	fclose(HA);
	
	/* Message */
	MESSAGE("Byteswapping required... ");
	
	/* Set starting time */
	s = clock();
	
	/* Check which endian to swap from */
	if(*buff == 0x80) goto end_no_swap; else
	if(*buff == 0x37) goto swap_loop_v64; else
	if(*buff == 0x40) goto swap_loop_little; else
	goto error_no_endian;

	/* Swap loop, v64 endian */
	swap_loop_v64:
	MESSAGE("swapping from V64 endian.\n");
	for(i=0;i<filesize;i+=16){
		buff2[0]=buff[i];
		buff2[1]=buff[i+1];
		buff2[2]=buff[i+2];
		buff2[3]=buff[i+3];
		buff2[4]=buff[i+4];
		buff2[5]=buff[i+5];
		buff2[6]=buff[i+6];
		buff2[7]=buff[i+7];
		buff2[8]=buff[i+8];
		buff2[9]=buff[i+9];
		buff2[10]=buff[i+10];
		buff2[11]=buff[i+11];
		buff2[12]=buff[i+12];
		buff2[13]=buff[i+13];
		buff2[14]=buff[i+14];
		buff2[15]=buff[i+15];
		buff[i]=buff2[1];
		buff[i+1]=buff2[0];
		buff[i+2]=buff2[3];
		buff[i+3]=buff2[2];
		buff[i+4]=buff2[5];
		buff[i+5]=buff2[4];
		buff[i+6]=buff2[7];
		buff[i+7]=buff2[6];
		buff[i+8]=buff2[9];
		buff[i+9]=buff2[8];
		buff[i+10]=buff2[11];
		buff[i+11]=buff2[10];
		buff[i+12]=buff2[13];
		buff[i+13]=buff2[12];
		buff[i+14]=buff2[15];
		buff[i+15]=buff2[14];
	}
	goto swap_end;
	
	/* Swap from little endian */
	swap_loop_little:
	MESSAGE("swapping from little endian.\n");
	for(i=0;i<filesize;i+=16){
		buff2[0]=buff[i];
		buff2[1]=buff[i+1];
		buff2[2]=buff[i+2];
		buff2[3]=buff[i+3];
		buff2[4]=buff[i+4];
		buff2[5]=buff[i+5];
		buff2[6]=buff[i+6];
		buff2[7]=buff[i+7];
		buff2[8]=buff[i+8];
		buff2[9]=buff[i+9];
		buff2[10]=buff[i+10];
		buff2[11]=buff[i+11];
		buff2[12]=buff[i+12];
		buff2[13]=buff[i+13];
		buff2[14]=buff[i+14];
		buff2[15]=buff[i+15];
		buff[i]=buff2[3];
		buff[i+1]=buff2[2];
		buff[i+2]=buff2[1];
		buff[i+3]=buff2[0];
		buff[i+4]=buff2[7];
		buff[i+5]=buff2[6];
		buff[i+6]=buff2[5];
		buff[i+7]=buff2[4];
		buff[i+8]=buff2[11];
		buff[i+9]=buff2[10];
		buff[i+10]=buff2[9];
		buff[i+11]=buff2[8];
		buff[i+12]=buff2[15];
		buff[i+13]=buff2[14];
		buff[i+14]=buff2[13];
		buff[i+15]=buff2[12];
	}
	
	/* Update counter */
	swap_end:
	e=clock();
	
	/* Write file to disk */
	if(!(HA=fopen(filename,"wb")))
		ERROR("Unable to reopen \"%s\" for writing. ",filename);
	fseek(HA,0,SEEK_SET);
	fwrite(buff,1,filesize,HA);
	fclose(HA);
	free(buff);
	
	/* Reopen file handle normally */
	if(!(HA = fopen(filename, "rb")))
		ERROR("Unable to reopen \"%s\" for reading. ",filename);
	
	/* Great success */
	MESSAGE("Swapping complete! Time taken: %.2fs, swapped %.2f words per sec.\n",
	((double)e-s)/CLOCKS_PER_SEC,(double)(filesize/4)/(((double)e-s)/CLOCKS_PER_SEC));
	return;
	
	/* Uh oh, no endian found */
	error_no_endian:
	free(buff);
	ERROR("Unable to detect ROM's endian! ");
	return;
	
	/* No swapping required */
	end_no_swap:
	free(buff);
	return;
	
	#undef HA
}
