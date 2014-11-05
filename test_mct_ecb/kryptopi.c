#include "serial.h"
#include "aes.h"
#include "memory.h"

/*
 *  Monte Carlo ECB Test
 */
int notmain ( void ) {

	aes_context aes;

	unsigned char key[16] = {0x8d, 0x2e, 0x60, 0x36, 0x5f, 0x17, 0xc7, 0xdf, 0x10, 0x40, 0xd7, 0x50, 0x1b, 0x4a, 0x7b, 0x5a};
	unsigned char input [16] = {0x59, 0xb5, 0x08, 0x8e, 0x6d, 0xad, 0xc3, 0xad, 0x5f, 0x27, 0xa4, 0x60, 0x87, 0x2d, 0x59, 0x29};
	unsigned char pt[16];
	unsigned char ct[16];
        int i, j, x;
	init_uart();
        
        memcpy(pt, input, 16);

        // MONTE CARLO ECB ALGORITHM
        for(i=0; i<3; i++) {
                aes_setkey_enc( &aes, key, 128 );

                serial_write((char*)key, 16);
                serial_write((char*)pt, 16);

                for(j=0; j<1000; j++) {
                        aes_crypt_ecb( &aes, AES_ENCRYPT, pt, ct );
                         memcpy(pt, ct, 16);
                }
                serial_write((char*)ct, 16);
                
                for(x=0; x<16;x++){
                        key[x] = key[x] ^ ct[x];
                }
        }
        
    return(0);

}