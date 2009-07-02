/***********************************
	SIMPLE PROGRESS BAR
***********************************/
#include <stdio.h>
#include "progbar.h"

u16 draw_bar (s32 bar_length, s32 min, s32 max, s32 current, u8 type, u8 show){
	/* example:
	show:
	0 bar only
	1 bar w/ percent only
	2 bar w/ min out of max
	3 bar w/ percent and min out of max
	
	type: measurement:
	0 nothing
	1 kbytes
	2 mbytes
	*/
	/* shift to positive (if required) */
	u32 tmp=0, bars, amnt=0, i; double percent;
	u8 temp[256]; double ma, mi; u8 temp2[128];
	
	/* calculate amount of bars to write */
	if(min<0||min>0) tmp=-min;
	min+=tmp;
	max+=tmp;
	current+=tmp;
	
	/* do the calculations */
	bars=(bar_length*current)/max;
	percent=(double)current/(double)max;
	switch(type){
		case 1: mi=(double)current/1024; ma=(double)max/1024; sprintf((char*)temp2,"KB"); break;
		case 2: mi=(double)current/1024/1024; ma=(double)max/1024/1024; sprintf((char*)temp2,"MB"); break;
	}
	
	/*printf("%i,%.02f",bars,percent*100.00);*/
	
	/* print the bar */
	amnt+=printf("[");
	for(i=0;i<bars;i++) amnt+=printf("#");
	for(;i<bar_length;i++) amnt+=printf(" ");
	amnt+=printf("] "); 
	
	/*printf("%i %i %.02f %.02f",show,type,mi,ma); getchar();*/
	
	/* info */
	switch(show){
		case 1:
		amnt+=printf("%03.02f%%",percent*100);
		break;
		
		case 2:
		if(type!=0)
			sprintf((char*)temp,"%.02f/%.02f%s",mi,ma,temp2);
		else
			sprintf((char*)temp,"%i/%i",(int)min,(int)current);
		amnt+=printf("%s",temp);
		break;
		
		case 3:
		amnt+=printf("%03.02f%% ",percent*100);
		if(type!=0)
			sprintf((char*)temp,"%.02f/%.02f%s",mi,ma,temp2);
		else
			sprintf((char*)temp,"%i/%i",(int)min,(int)current);
		amnt+=printf("%s",temp);
		break;
	}
	
	/* flush */
	fflush(stdout);

	return amnt;
}

void erase_previous (u16 amount){
	u32 i; for(i=0;i<amount;i++) printf("\b");
	fflush(stdout);
}
