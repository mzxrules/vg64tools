#ifndef __NOVL_MESG_H__
#define __NOVL_MESG_H__

#include <stdarg.h>
#include "novl.h"
#include "ansi.h"

extern int mk_mesg_f ( char *, char *, va_list );
extern int mk_mesg ( char *, char *, ... );
extern int MESG ( char *, ... );
extern int ERROR ( char *, ... );

 #ifdef NOVL_DEBUG
  extern int DEBUG ( char *, ... );
  extern int DEBUG_R ( char *, ... );
 #else
  #define DEBUG(...)
  #define DEBUG_R(...)
 #endif /* NOVL_DEBUG */

#endif /* __NOVL_MESG_H__ */

