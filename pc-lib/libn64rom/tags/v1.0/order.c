#include <stdint.h>

#define W32(x)     \
(                  \
    (x)[0] << 24 | \
    (x)[1] << 16 | \
    (x)[2] << 8  | \
    (x)[3]         \
)

typedef void (*N64ROMSwapFunc)( void *, int );

static void
swap16le ( void * d, int l )
{
    uint32_t * s, * p;
    
    p = (void*)((int)d + l);
    s = d;
    
    while( s != p )
    {
        *s = (*s >> 16) | (*s & 0xFFFF);
        s++;
    }
}

static void
swap32le ( void * d, int l )
{
    uint32_t * s, * p;
    
    p = (void*)((int)d + l);
    s = d;
    
    while( s != p )
    {
        *s = W32( (unsigned char*)s );
        s++;
    }
}

struct swap_t
{
    const char *    name;
    uint32_t        identifier;
    N64ROMSwapFunc  swap;
};

static const struct swap_t
accepted_types[] =
{
    { "little endian (DCBA)",        0x40123780, swap32le },
    { "16-bit little endian (BADC)", 0x37804012, swap16le },
    { "Big endian (ABCD)",           0x80371240, NULL     },
    { NULL, 0, NULL }
};
