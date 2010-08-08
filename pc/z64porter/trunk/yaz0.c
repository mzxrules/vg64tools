/*
 yaz0 decompression and compression, concatenated from yaz0dec.cpp
 and yaz0enc.c. Original header of both files follow
Decompression:
    //version 1.0 (20050213)
    //by thakis
Compresssion:
    Yaz0 recompressor
    -----------------
    Original by `shevious`, made into more of a UNIX
    program by ZZT32 (http://64.vg/)
*/

#include "yaz0.h"

uint8_t * Data;
int dstSize;
int pos;

uint32_t toDWORD(uint32_t d)
{
  uint8_t w1 = d & 0xFF;
  uint8_t w2 = (d >> 8) & 0xFF;
  uint8_t w3 = (d >> 16) & 0xFF;
  uint8_t w4 = d >> 24;
  return (w1 << 24) | (w2 << 16) | (w3 << 8) | w4;
}

/* Compression... */

// simple and straight encoding scheme for Yaz0
uint32_t simpleEnc(uint8_t* src, int size, int pos, uint32_t *pMatchPos)
{
  int startPos = pos - 0x1000, j, i;
  uint32_t numBytes = 1;
  uint32_t matchPos = 0;

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
uint32_t nintendoEnc(uint8_t* src, int size, int pos, uint32_t *pMatchPos)
{
  uint32_t numBytes = 1;
  static uint32_t numBytes1;
  static uint32_t matchPos;
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



int encodeYaz0(uint8_t* src, int srcSize, uint8_t * Data)
{
  yaz0_Ret r = { 0, 0 };
  uint8_t dst[24];    // 8 codes * 3 bytes maximum
  int dstSize = 0;
  int i;
  
  uint32_t validBitCount = 0; //number of valid bits left in "code" byte
  uint8_t currCodeByte = 0;
  while(r.srcPos < srcSize)
  {
    uint32_t numBytes;
    uint32_t matchPos;
    uint32_t srcPosBak;

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
      uint32_t dist = r.srcPos - matchPos - 1; 
      uint8_t byte1, byte2, byte3;

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
      Data[pos] = currCodeByte;
      pos++;
      for (i=0;i</*=*/r.dstPos;pos++,i++)
        Data[pos] = dst[i];
      dstSize += r.dstPos+1;

      srcPosBak = r.srcPos;
      currCodeByte = 0;
      validBitCount = 0;
      r.dstPos = 0;
    }
  }
  if(validBitCount > 0)
  {
    Data[pos] = currCodeByte;
    pos++;
    for (i=0;i</*=*/r.dstPos;pos++,i++)
      Data[pos] = dst[i];
    dstSize += r.dstPos+1;

    currCodeByte = 0;
    validBitCount = 0;
    r.dstPos = 0;
  }
    
  return dstSize;
}



uint8_t * encodeAll(uint8_t * src, int srcSize )
{
  Data = (uint8_t*)malloc(srcSize + 0x20); //should be enough, sometimes outsize > insize; thats what the +0x20 is for

  // write 4 bytes yaz0 header
  Data[0] = 'Y';
  Data[1] = 'a';
  Data[2] = 'z';
  Data[3] = '0';
  
  // write 4 bytes uncompressed size
  Data[4] = (srcSize >> 24) & 0xFF;
  Data[5] = (srcSize >> 16) & 0xFF;
  Data[6] = (srcSize >> 8) & 0xFF;
  Data[7] = srcSize & 0xFF;

  // write 8 bytes unused dummy 
  memset(&Data[8], 0, 8);
  
  pos=16;
  
  //encode
  dstSize = encodeYaz0(src, srcSize, Data);
  
  return Data; 
}

