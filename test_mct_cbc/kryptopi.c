#include "serial.h"
#include "aes.h"
#include "memory.h"

/*
 * Monte Carlo CBC test
 */
int notmain ( void ) {

	aes_context aes;

	unsigned char key[16] = {0x9d, 0xc2, 0xc8, 0x4a, 0x37, 0x85, 0x0c, 0x11, 0x69, 0x98, 0x18, 0x60, 0x5f, 0x47, 0x95, 0x8c};
	unsigned char iv[16] = {0x25, 0x69, 0x53, 0xb2, 0xfe, 0xab, 0x2a, 0x04, 0xae, 0x01, 0x80, 0xd8, 0x33, 0x5b, 0xbe, 0xd6};
        unsigned char input [16] = {0x2e, 0x58, 0x66, 0x92, 0xe6, 0x47, 0xf5, 0x02, 0x8e, 0xc6, 0xfa, 0x47, 0xa5, 0x5a, 0x2a, 0xab};
        unsigned char pt[16];
	unsigned char ct[16];
	unsigned char ct_old[16];
	unsigned char iv_before[16];    //since the algo modifies the IV
        int i, j, x;
        
	init_uart();
        
        memcpy(pt, input, 16);

        // MONTE CARLO CBC ALGORITHM
        for(i=0; i<3; i++) {
                aes_setkey_enc( &aes, key, 128 );

                serial_write((char*)key, 16);
                serial_write((char*)iv, 16);
                serial_write((char*)pt, 16);

                for(j=0; j<1000; j++) {
                    memcpy(iv_before, iv, 16);
                    aes_crypt_cbc(&aes, AES_ENCRYPT, 16, iv, pt, ct);
                    if(j==0) {
                        memcpy(pt, iv_before, 16);
                    }else{
                        memcpy(pt, ct_old, 16);
                    }
                    memcpy(ct_old, ct, 16);
                    memcpy(iv, ct, 16);
                }
                serial_write((char*)ct, 16);
                
                for(x=0; x<16;x++){
                        key[x] = key[x] ^ ct[x];
                }
        }
        
    return(0);

}