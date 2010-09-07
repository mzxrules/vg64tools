#ifndef __LN64ROM_CRC_H
#define __LN64ROM_CRC_H

void n64rom_crc ( N64Rom * h, unsigned *dest );
void n64rom_crc_fix ( N64Rom * r );
int n64rom_crc_quick ( char * filename );

#endif
