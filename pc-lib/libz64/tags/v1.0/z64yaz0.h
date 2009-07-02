/********************************
* Zelda 64 Compression Handling *
********************************/
#ifndef __LZ64_YAZ0_H
#define __LZ64_YAZ0_H

/* Functions */
extern void z64yaz0_decode ( unsigned char * src, unsigned char * dst, int uncompressedSize );
extern int z64yaz0_encode ( void * bin, int len, void ** target, float * prog );

#endif /* __LZ64_YAZ0_H */
