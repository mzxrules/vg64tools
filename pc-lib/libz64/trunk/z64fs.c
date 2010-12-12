/******************************
* Zelda 64 Filesystem Library *
******************************/
#include <z64.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <z64yaz0.h>
#include <z64fs.h>

/* Constants */
#define SEARCH_STRING   "zelda@"
#define CHUNK_SIZE      (512 * 1024)
#define END_ADDR        (1 * 1024 * 1024)

/* Macros */
#define U32(x)      ((x)[0] << 24 | (x)[1] << 16 | (x)[2] << 8 | (x)[3])
#define setU32(x,val)			\
{					\
	(x)[0] = ((val)>>24) & 0xFF;	\
	(x)[1] = ((val)>>16) & 0xFF;	\
	(x)[2] = ((val)>>8) & 0xFF;	\
	(x)[3] = (val) & 0xFF;		\
}

/* Create a filesystem context */
struct Zelda64FileTable *
z64fs_open ( FILE * handle )
{
    unsigned char * buffer, * seek;
    Z64FS         * ret;
    unsigned        i, tstart, k;
    
    /* Create return */
    ret = calloc( sizeof(Z64FS), 1 );
    
    /* Allocate buffer memory */
    buffer = malloc( CHUNK_SIZE );
    
    /* Seek past standard boot routines and such */
    fseek( handle, 0x1060, SEEK_SET );
    
    /* Fill buffer */
searchloop:
    fread( buffer, 1, CHUNK_SIZE, handle );
    
    /* Scan through it in search of key */
    for( i = 0; i < CHUNK_SIZE; i += 16 )
        
        /* Compare */
        if( !memcmp( SEARCH_STRING, buffer + i, 6 ) )
            
            /* Found */
            goto fs_found;
    
    /* Nothing found as of yet, check conditions */
    if( ftell(handle) + CHUNK_SIZE >= END_ADDR )
        goto fs_not_found; /* nothing */
    
    /* Otherwise, continue */
    goto searchloop;
    
    /* ~~ */
    
    /* Found filesystem */
fs_found:
    
    /* Repoint buffer */
    fseek( handle, ftell(handle) - CHUNK_SIZE + i, SEEK_SET );
    fread( buffer, 1, CHUNK_SIZE, handle );
    
    /* Read creator */
    seek  = buffer;
    seek += sprintf( ret->creator, "%s", buffer );
    
    /* Seek ahead to date */
    while( !*seek && seek - buffer < 64 )
        seek++;
    
    /* Copy it */
    seek += sprintf( ret->date, "%s", seek );
    
    /* Discover entry */
    for( k = (((seek - buffer) >> 4) + 1) << 4; ; k += 16 )
        if( U32(&buffer[k + 4]) == 0x00001060 )
        {
            tstart = k;
            break;
        }
    
    /* Read address of DMA data */
    ret->start = U32(buffer + tstart + 2 * 16);
    ret->end   = U32(buffer + tstart + 2 * 16 + 4);
    
    /* Set filecount *
    for( count = 1; U32(&buffer[tstart+count*16]); count++ );
        ret->filecount = count;*/
    ret->filecount = (ret->end - ret->start) / 0x10;
    
    /* Set address *
    ret->start = ftell(handle) - CHUNK_SIZE + tstart;
    ret->end   = ret->start + count * 16;*/
    
    /* Allocate memory for final storage */
    ret->files = malloc( ret->end - ret->start );
    
    /* Fill */
    for( i = 0; i < ret->end - ret->start; i += 16 )
    {
        ret->files[i/16].vstart = U32(buffer + tstart + i     );
        ret->files[i/16].vend   = U32(buffer + tstart + i +  4);
        ret->files[i/16].start  = U32(buffer + tstart + i +  8);
        ret->files[i/16].end    = U32(buffer + tstart + i + 12);
    }
    
    /* All done */
    free( buffer );
    return ret;
    
    /* ~~ */
    
    /* Filesystem not found */
fs_not_found:
    free( buffer );
    free( ret    );
    return NULL;
}

/* Return the decompressed size of a filesystem */
unsigned z64fs_size_virt ( Z64FS * h )
{
    unsigned i, total = 0;
    
    /* Loop through each entry */
    for( i = 0; i < z64fs_entries(h); i++ )
    {
        /* Does this file exist? */
        if( ZFileExists(h, i) )
            total += ZFileVirtSize(h, i);
    }
    
    return total;
}

/* Return the physical size of a filesystem */
unsigned z64fs_size_phys ( Z64FS * h )
{
    unsigned i, total = 0;
    
    /* Loop through each entry */
    for( i = 0; i < z64fs_entries(h); i++ )
    {
        /* Does this file exist? */
        if( ZFileExists(h, i) )
            total += ZFileRealSize(h, i);
    }
    
    return total;
}

/* Close a handle */
void z64fs_close ( Z64FS * h )
{
    free( h->files );
    free( h );
}

/* Read a file */
void z64fs_read_file ( Z64 * h, int id, unsigned char * dest )
{
	const Z64FSEntry * f = z64fs_file( h->fs, id );
	
	fseek( h->handle, f->start, SEEK_SET );
	fread( dest, 1, Z_FILESIZE_PHYS(f), h->handle );
	
	/* Compressed? */
	if( Z_COMPRESSED(f) )
	{
		unsigned char * tmp = malloc( ZFileVirtSize(h->fs, id) );
		z64yaz0_decode( dest + 16, tmp, ZFileVirtSize(h->fs, id) );
		memcpy( dest, tmp, ZFileVirtSize(h->fs, id) );
		free( tmp );
	}
}

/* Get a file ID for a start offset */
int
z64fs_search_offset( Z64 * h, guint32 VirtStart)
{
	int i;
	for(i = 0; i < z64fs_entries(h->fs); i++)
	{
		if(ZFileVirtStart(h->fs, i) == VirtStart)
			return i;
	}
	return -1;
}

int
z64fs_max_offset( Z64 * h, int ignore)
{
	signed int max=0,i;
	for(i = 0; i < z64fs_entries(h->fs); i++)
	{
		if(i != ignore && (signed)ZFileEnd(h->fs, i) > max)
			max = (signed)ZFileEnd(h->fs, i);
	}
	return max;
}

void
z64fs_write_file_ptr( Z64 * h, int id, Z64FSEntry *file_entry )
{
    char buff[16];
    
    memcpy(&h->fs->files[id], file_entry, sizeof(Z64FSEntry));
    
    setU32(buff+0x0, file_entry->vstart);
    setU32(buff+0x4, file_entry->vend);
    setU32(buff+0x8, file_entry->start);
    setU32(buff+0xC, file_entry->end);
    
    /* write pointers */
    fseek(h->handle, h->fs->start + (id * 0x10), SEEK_SET);
    fwrite(buff, 1, 0x10, h->handle);
}

/* Save a file - write virt and phys pointers, data */
void
z64fs_write_file(Z64 * h, int id, Z64FSEntry *file_entry, unsigned char * data, size_t siz)
{
    if(memcmp(data, "Yaz0", 4))
        file_entry->end = 0;
    
    /* write pointer in filetable */
    z64fs_write_file_ptr( h, id, file_entry );
    
    /* write data */
    fseek(h->handle, file_entry->start, SEEK_SET);
    fwrite(data, 1, siz, h->handle);
}

/* internal */
int
filecmp(const void *a, const void *b)
{
    Z64FSEntry *f1, *f2;
    f1 = (Z64FSEntry*)a;
    f2 = (Z64FSEntry*)b;
    if(!f1->vend)
        return LONG_MAX;
    else if(!f2->vend)
        return LONG_MIN;
    return ( f1->vstart - f2->vstart );
}

int
z64fs_fix_filetable( Z64 * h )
{
    int i;
    if(h->fs == NULL)
        return -1;
    
    qsort(h->fs->files, h->fs->filecount, sizeof(Z64FSEntry), filecmp);
    
    fseek(h->handle, h->fs->start, SEEK_SET);
    for(i = 0; i < h->fs->filecount && ZFileVirtEnd(h->fs, i+1); i++)
    {
        z64fs_write_file_ptr( h, i, &h->fs->files[i] );
      #ifdef DEBUG
        printf("%04i %08X %08X %08X %08X\n", i,
               ZFileVirtStart(h->fs, i), ZFileVirtEnd(h->fs, i),
               ZFileRealStart(h->fs, i), ZFileRealRealEnd(h->fs, i)
        );
      #endif
    }
    
    return 0;
}
