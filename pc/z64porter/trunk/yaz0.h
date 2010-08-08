#ifndef YAZ0_H
 #define YAZ0_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct
{
  int srcPos, dstPos;
} yaz0_Ret;

typedef struct
{
   char * buffer;
   int size;
} siz_buffer;

uint8_t * Data;
int dstSize;
int sflag;
int pos;

/* functions */
uint8_t * encodeAll(uint8_t * src, int srcSize );
uint32_t simpleEnc(uint8_t* src, int size, int pos, uint32_t *pMatchPos);
uint32_t nintendoEnc(uint8_t* src, int size, int pos, uint32_t *pMatchPos);
int encodeYaz0(uint8_t* src, int srcSize, uint8_t * Data);
siz_buffer decodeAll(uint8_t * src, int srcSize);
yaz0_Ret decodeYaz0(uint8_t* src, int srcSize, uint8_t* dst, int uncompressedSize);
uint32_t toDWORD(uint32_t d);

#endif
