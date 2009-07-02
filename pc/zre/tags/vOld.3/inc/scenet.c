/*********************************
* Scene Table Handler for OoT/MM *
*********************************/
#include <stdio.h>
#include "../zre.h"

/* all of the good scene stuff is in z64l/ */

/*
	!!! NOTICE !!!
	Just a head's up... this file is really messy, partly because I 
	did no planning at all before writing it. Regardless, everything
	is here and in working order.
*/

/* Static (to this func) vars */
static struct scenetman sconf;
static Z64ST_MM  *s_mm;
static Z64ST_OOT *s_oot;
static u32 *mmp;
static u32 *oop;

/*
struct entry_oot {
	u32 o1;
	u32 o2;
	u32 i1;
	u32 i2;
	u32 o;
};
struct entry_oot **e_oot;
int entcmp ( struct entry_oot **a, struct entry_oot **b );
*/

int zre_scene_main ( void ){
	
	/*
		Status codes:
		0 = done nothing yet; not even code.zasm
		1 = code.zasm found; scene table read, waiting for first offset
		2 = continual reading
		3 = done
	*/
	
	/* Variables */
	u32 i, a, *p;
	
	/* If we're detecting using filenames it'll already be perfect */
	if(!conf.skip_names || conf.notable)
		return 0;
	
	/* Do something depending on game */
	switch(rident){
		
		case __GAME_OOT:
		switch(sconf.status){
			case 0:
			if(fbuff.type == type_zasm){
				
				/* Oh cool we found it; detect the scene table */
				s_oot = z64st_oot_init_r(fbuff.data, fbuff.length);
				
				/* Check */
				if(!s_oot){
					DEBUGA(
					MESSAGE("Well, we found code.zasm but were unable to detect the "
					"scene table. Sorry about that.\n");getchar();return 0,
					return 0);
				}					
				
				/* Read first offsets into handle */
				z64st_oot_read_next(s_oot);
				
				/* Some debugging info... */
				DEBUG(MESSAGE("Awesome, found scene table. Quick dump: %X-%X\n",
				s_oot->t_start,s_oot->t_end);
				z64st_oot_dump_small(s_oot);
				MESSAGE("Location in ROM: %08X -> %08X (rough estimation)\n",
				ZF1START(fsh)+s_oot->t_start,ZF1START(fsh)+s_oot->t_end));
				
				/* Ok, now we have to sort it 
				e_oot = malloc(sizeof(struct entry_oot *)*((s_oot->t_end-s_oot->t_start)/20));*/
				oop = (u32*)malloc((s_oot->t_end-s_oot->t_start)/20 * sizeof(u32));
				for(i=0; i<(s_oot->t_end-s_oot->t_start)/20; i++)
					oop[i] = BYTES2LONG(i*20 + s_oot->table);
				
				/* Go go gadget qsort! 
				qsort(e_oot,(s_oot->t_end-s_oot->t_start)/20,4,entcmp);*/
				
				DEBUG(
					MESSAGE("Prepped. Want to see it? <Y/N> ");
					if(toupper(GETINPUT())=='Y'){
						for(i=0;i<(s_oot->t_end-s_oot->t_start)/20;i++)
							printf("oop[%03u] = 0x%08X\n",i,oop[i]);
						GETINPUT();
					}
				);
				
				/* Free other copy of table */
				z64st_oot_close(s_oot);
				
				/* Neato, now we wait */
				sconf.status = 1;
			}
			break;
			
			case 1:
				/* Goody, everything is set up... look for scene offset */
				if(search_addr_oot(ZF1START(fsh))){
					
					/* Debug */
					DEBUG(MESSAGE("Ok, beginning scene/map identifying now.\n"));
					
					/* Got one! */
					sconf.status = 2;
					
					/* Set file type */
					fbuff.type = type_zscene;
					return 1;
				}
			break;
			
			
			case 2:
				/* ~~ */
				if(search_addr_oot(ZF1START(fsh))){
					
					DEBUG(MESSAGE("Scene found @ %08X %08X.\n",ZF1START(fsh),ZF1END(fsh)));
					
					/* Scene */
					fbuff.type = type_zscene;
					return 1;
					
				}else if(fbuff.type == type_zscene){
					
					DEBUG(MESSAGE("Strange... scene encountered but no scene table entry?\n");
					for(i=0,a=sconf.pos-1; i < 3; i++,a++)
						printf("oop[%03u] = 0x%08X\n",a,oop[a]);
					getchar());
				
				}else if(Z1FSIZE(fsh)>0x10){
					/* Map */
					fbuff.type = type_zmap;
					return 1;
				}else{
					/* Out! */
					sconf.status = 1;
				}	
			break;
			
			default:
				ERROR("Internal error.\n");
		}
		break;
		
		
		/* Majora's Mask */
		case __GAME_MM:
		switch(sconf.status){
			/* No scene table found yet */
			case 0:
			if(fbuff.type == type_zasm){
				/* Opportunity! */
				s_mm = z64st_mm_init_r(fbuff.data, fbuff.length);
				
				/* No scene table found :/ */
				if(!s_mm){
					DEBUG(MESSAGE("Odd. Code block found, but no scene table detected...\n"));
					conf.noscene = true;
					return 0;
				}
				
				/* Debug! */
				DEBUG(
				MESSAGE("Excellent, scene table found @: $%08X -> $%08X.\nDump offsets? <Y/N> ",
				ZF1START(fsh)+s_mm->t_start,ZF1START(fsh)+s_mm->t_end)
				);
				
				/* Load offsets into RAM properly */
				mmp = (u32*)malloc(z64st_mm_num_entries(s_mm)*sizeof(u32));
				for(i=0;i<z64st_mm_num_entries(s_mm);i++)
					mmp[i]=BYTES2LONG(s_mm->table + i*16);
				
				/* Moar debug */
				DEBUG(
				if(toupper(GETINPUT()) == 'Y'){
					for(i=0;i<z64st_mm_num_entries(s_mm);i++)
						MESSAGE("offset[%03u] = 0x%08X\n",i,mmp[i]);
					GETINPUT();
				});
				
				/* Set status */
				sconf.status = 1;
			}
			break;
			
			/* Scene table found; waiting for first scene */
			case 1:
			if(search_addr_mm(mmp,ZF1START(fsh))){
				
				/* Set type */
				fbuff.type = type_zscene;
				
				/* Debug */
				DEBUG(MESSAGE("Ok, beginning scene/map identifying now.\n"));
				
				/* Set status */
				sconf.status = 2;
				return 1;
			}
			break;
			
			/* In scene/map pattern now */
			case 2:
			if(search_addr_mm(mmp,ZF1START(fsh))){
				
				/* Debug */
				DEBUG(MESSAGE("Scene found @ %08X %08X.\n",ZF1START(fsh),ZF1END(fsh)));
				
				/* Set type */
				fbuff.type = type_zscene;
				return 1;
				
			}else if(Z1FSIZE(fsh)>0x10){
				
				/* Map */
				fbuff.type = type_zmap;
				return 1;
				
			} else {
				
				/* Invalid */
				sconf.status = 1;
			}
			break;	
		}
		break;

		case __GAME_UNK:
			return 0;
		break;
		
		default:
			return 0;
	}
	return 0;
}

/*int entcmp ( struct entry_oot **a, struct entry_oot **b ){
	if((*a)->o1 < (*b)->o1)
		return -1;
	else if((*a)->o1 == (*b)->o1)
		return 0;
	else
		return 1;
}*/

int search_addr_oot ( u32 addr ){
	
	int i;
	for(i=0;i<(s_oot->t_end-s_oot->t_start)/20;i++)
		if(oop[i] == addr)
			return 1;
	return 0;
}

int search_addr_mm (u32 *p, u32 addr){
	int i;
	for(i=0;i<z64st_mm_num_entries(s_mm);i++)
		if(p[i] == addr)
			return 1;
	return 0;
}
