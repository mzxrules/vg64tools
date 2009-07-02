/********************************
* Zelda 64 Compression Handling *
********************************/
#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "z64yaz0.h"

void z64yaz0_decode (unsigned char * src, unsigned char * dst, int uncompressedSize)
{
  int srcPlace = 0, dstPlace = 0; /*current read/write positions*/
  
  unsigned int validBitCount = 0; /*number of valid bits left in "code" byte*/
  unsigned char currCodeByte = 0;
  
  while(dstPlace < uncompressedSize)
  {
    /*read new "code" byte if the current one is used up*/
    if(validBitCount == 0)
    {
      currCodeByte = src[srcPlace];
      ++srcPlace;
      validBitCount = 8;
    }
    
    if((currCodeByte & 0x80) != 0)
    {
      /*straight copy*/
      dst[dstPlace] = src[srcPlace];
      dstPlace++;
      srcPlace++;
    }
    else
    {
      /*RLE part*/
      unsigned char byte1 = src[srcPlace];
      unsigned char byte2 = src[srcPlace + 1];
      srcPlace += 2;
      
      unsigned int dist = ((byte1 & 0xF) << 8) | byte2;
      unsigned int copySource = dstPlace - (dist + 1);

      unsigned int numBytes = byte1 >> 4;
      if(numBytes == 0)
      {
        numBytes = src[srcPlace] + 0x12;
        srcPlace++;
      }
      else
        numBytes += 2;

      /*copy run*/
      int i;
      for(i = 0; i < numBytes; ++i)
      {
        dst[dstPlace] = dst[copySource];
        copySource++;
        dstPlace++;
      }
    }
    
    /*use next bit from "code" byte*/
    currCodeByte <<= 1;
    validBitCount-=1;    
  }
}


/* ----------------------------------------------
   Yaz0 encoder
   ---------------------------------------------- */

/*
    Original header:
     //version 1.0 (20050707)
     //by shevious
     //Thanks to thakis for yaz0dec 1.0.
*/

typedef unsigned char u8;
typedef unsigned int u32;

static u32 toDWORD(u32 d)
{
  u8 w1 = d & 0xFF;
  u8 w2 = (d >> 8) & 0xFF;
  u8 w3 = (d >> 16) & 0xFF;
  u8 w4 = d >> 24;
  return (w1 << 24) | (w2 << 16) | (w3 << 8) | w4;
}

typedef struct Ret
{
  int srcPos, dstPos;
}
Ret;


/* Progress indicator */
static float * progress;

/* Target */
static GByteArray * output;


// simple and straight encoding scheme for Yaz0
static u32 simpleEnc(u8* src, int size, int pos, u32 *pMatchPos)
{
  int startPos = pos - 0x1000, j, i;
  u32 numBytes = 1;
  u32 matchPos = 0;

  if (startPos < 0)
    startPos = 0;
  for (i = startPos; i < pos; i++)
  {
    for (j = 0; j < size-pos; j++)
    {
      if (src[i+j] != src[j+pos])
        break;
    }
    if (j > numBytes)
    {
      numBytes = j;
      matchPos = i;
    }
  }
  *pMatchPos = matchPos;
  if (numBytes == 2)
    numBytes = 1;
  return numBytes;
}



// a lookahead encoding scheme for ngc Yaz0
static u32 nintendoEnc(u8* src, int size, int pos, u32 *pMatchPos)
{
  u32 numBytes = 1;
  static u32 numBytes1;
  static u32 matchPos;
  static int prevFlag = 0;

  // if prevFlag is set, it means that the previous position was determined by look-ahead try.
  // so just use it. this is not the best optimization, but nintendo's choice for speed.
  if (prevFlag == 1) {
    *pMatchPos = matchPos;
    prevFlag = 0;
    return numBytes1;
  }
  prevFlag = 0;
  numBytes = simpleEnc(src, size, pos, &matchPos);
  *pMatchPos = matchPos;

  // if this position is RLE encoded, then compare to copying 1 byte and next position(pos+1) encoding
  if (numBytes >= 3) {
    numBytes1 = simpleEnc(src, size, pos+1, &matchPos);
    // if the next position encoding is +2 longer than current position, choose it.
    // this does not guarantee the best optimization, but fairly good optimization with speed.
    if (numBytes1 >= numBytes+2) {
      numBytes = 1;
      prevFlag = 1;
    }
  }
  return numBytes;
}



static int encodeYaz0(u8* src, int srcSize, FILE* dstFile)
{
  Ret r = { 0, 0 };
  u8 dst[24];    // 8 codes * 3 bytes maximum
  int dstSize = 0;
  
  u32 validBitCount = 0; //number of valid bits left in "code" byte
  u8 currCodeByte = 0;
  while(r.srcPos < srcSize)
  {
    u32 numBytes;
    u32 matchPos;
    u32 srcPosBak;

    numBytes = nintendoEnc(src, srcSize, r.srcPos, &matchPos);
    if (numBytes < 3)
    {
      //straight copy
      dst[r.dstPos] = src[r.srcPos];
      r.dstPos++;
      r.srcPos++;
      //set flag for straight copy
      currCodeByte |= (0x80 >> validBitCount);
    }
    else 
    {
      //RLE part
      u32 dist = r.srcPos - matchPos - 1; 
      u8 byte1, byte2, byte3;

      if (numBytes >= 0x12)  // 3 byte encoding
      {
        byte1 = 0 | (dist >> 8);
        byte2 = dist & 0xff;
        dst[r.dstPos++] = byte1;
        dst[r.dstPos++] = byte2;
        // maximum runlength for 3 byte encoding
        if (numBytes > 0xff+0x12)
          numBytes = 0xff+0x12;
        byte3 = numBytes - 0x12;
        dst[r.dstPos++] = byte3;
      } 
      else  // 2 byte encoding
      {
        byte1 = ((numBytes - 2) << 4) | (dist >> 8);
        byte2 = dist & 0xff;
        dst[r.dstPos++] = byte1;
        dst[r.dstPos++] = byte2;
      }
      r.srcPos += numBytes;
    }
    validBitCount++;
    //write eight codes
    if(validBitCount == 8)
    {
      g_byte_array_append( output, &currCodeByte, 1 );
      //fwrite(&currCodeByte, 1, 1, dstFile);
	  g_byte_array_append( output, dst, r.dstPos );
      //fwrite(dst, 1, r.dstPos, dstFile);
      //fflush(dstFile);
      dstSize += r.dstPos+1;

      srcPosBak = r.srcPos;
      currCodeByte = 0;
      validBitCount = 0;
      r.dstPos = 0;
    }
	
	/* Update percentage */
	*progress = (r.srcPos+1)*100.0f / (float)srcSize;
	
	/*
      if ((r.srcPos+1)*100/srcSize != percent) {
        percent = (r.srcPos+1)*100/srcSize;
        fprintf(stderr, "\r%i%%", percent);
      }
	*/
  }
  if(validBitCount > 0)
  {
	
    g_byte_array_append( output, &currCodeByte, 1 );
    //fwrite(&currCodeByte, 1, 1, dstFile);
	g_byte_array_append( output, dst, r.dstPos );
    //fwrite(dst, 1, r.dstPos, dstFile);
    dstSize += r.dstPos+1;

    currCodeByte = 0;
    validBitCount = 0;
    r.dstPos = 0;
  }
    
  return dstSize;
}



static void encodeAll(u8 * src, int srcSize )
{
  char dummy[8];
  int dstSize;

  FILE * DataFile = stdout;

  // write 4 bytes yaz0 header
  g_byte_array_append( output, (void*)"Yaz0", 4 );
  //fwrite("Yaz0", 1, 4, DataFile);

  u32 Size=toDWORD(srcSize);
  // write 4 bytes uncompressed size
  g_byte_array_append( output, (void*)&Size, 4 );
  //fwrite(&Size, 1, 4, DataFile);

  memset(dummy, 0, 8);
  // write 8 bytes unused dummy 
  g_byte_array_append( output, (void*)dummy, 8 );
  //fwrite(dummy, 1, 8, DataFile);

  dstSize = encodeYaz0(src, srcSize, DataFile);
}


int z64yaz0_encode ( void * bin, int len, void ** target, float * prog )
{
	int v;
	
	/* Store progress bar pointer */
	progress = prog;
	
	/* Create new data buffer */
	output = g_byte_array_sized_new( len );
	
	/* Encode it */
	encodeAll( bin, len );
	
	/* Preserve final size */
	v = output->len;
	*target = output->data;
	g_free( output );
	
	/* Return length */
	return v;
}
	

