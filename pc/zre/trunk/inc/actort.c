/**************************
* ZRE ACTOR TABLE HANDLER *
**************************/
#include <stdio.h>
#include "../zre.h"

/* Variables */
struct {
	u8 status;
} aconf;
static Z64AT *ahandle;

int zre_actor_main ( void ){
	
	switch(aconf.status){
		case 0:
		if(fbuff.type == type_zasm){
			if(!(ahandle = zat_init(fbuff.data, fbuff.length))){
				DEBUG(MESSAGE("Tried to find actor table but failed.\n"));
				conf.noactor = true;
				return 0;
			}else{
				DEBUG(MESSAGE("Actor table found @: $%08X -> $%08X. Dump? <Y/N> ",
				ZF1START(fsh)+ahandle->start,ZF1START(fsh)+ahandle->end);
				if(toupper(GETINPUT()) == 'Y'){ zat_dump_handle(ahandle); GETINPUT();});
				aconf.status = 1;
				return 1;
			}
		}
		break;
		
		case 1:
		if(zre_actor_search(ZF1START(fsh))){
			DEBUG(MESSAGE("Actor found @: $%08X -> $%08X\n",
			ZF1START(fsh),ZF1END(fsh)));
			fbuff.type = type_zactor;
			return 1;
		}else{
			if(fbuff.type == type_zactor)
				fbuff.type = type_zdata;
			return 0;
		}
		break;
	}
	return 0;
}

int zre_actor_search ( u32 s ){
	int i;
	for(i=0; i<z64at_num_entries(ahandle); i++)
		if(ahandle->t[i].s == s)
			return 1;
	return 0;
}
