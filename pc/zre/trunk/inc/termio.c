#include <stdio.h>
#include <stdarg.h>
#include "../zre.h"

#ifdef WIN32
# define vsnprintf _vsnprintf
#endif /* WIN32 */

void MESSAGE (const char *format, ...){
	/* Vars */
	va_list ap;
	char buf[1024];
	
	/* Check that we are allowed to print */
	if(!conf.silent){
		va_start(ap, format);
		vsnprintf(buf, sizeof(buf)-1, format, ap);
		va_end(ap);
		fprintf(stdout, "%s", buf);
	}
}

int GETINPUT ( void ){
	int cur, prev = '\n';
	while((cur = getchar()) != '\n')
		prev = cur;
	return prev;
}

int READTOSTR ( char *str, int maxlen ){
	
	int i;
	
	for(i = 0; i < maxlen && (*str = getchar()) != '\n'; i++, str++);
	*str = 0;
	
	return i;
}
	
