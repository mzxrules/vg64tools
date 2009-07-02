/*************************
* ZRE: VARIOUS FUNCTIONS *
*************************/
#include <stdio.h>
#include "../zre.h"

/* str replace */
u8 str_replace (u8 *search_str, u8 *replace_str, u8 *source_str){
	/* lengths */
	u32 len1=strlen(search_str),len2=strlen(replace_str),
	len3=strlen(source_str),i,a,c; 
	if(len1<len2) goto fail; /* replace strings longer than search not supported */
	if(len3<len1||len3<len2) goto fail;
	
	/* main loop */
	for(i=0;i<len3-len1+1;i++){
		if(source_str[i]==search_str[0]){ /* ahmg potential match */
			for(a=0;a<len1;a++)
				if(source_str[i+a]!=search_str[a])
					break;
			if(a==len1) goto match;
		}
	}
	
	
	fail:
	return false;
	
	match: /* i contains location of the thang */
	
	for(a=i;a<len2+i;a++)
		source_str[a]=replace_str[a-i];
	/* shift down the rest of the elements if necessary */
	if(len1>len2){
		for(c=0;c<len3-(len1-len2)-a;c++)
			source_str[c+a]=source_str[c+a+(len1-len2)];
		source_str[c+a]=0;
	}
	/* good */
	return true;
}
