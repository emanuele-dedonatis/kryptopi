#include "serial.h"
#include "aes.h"
#include "memory.h"

/*
 *   Test for serial library:
 *      + Read and store from serial
 *      + Write to serial
 */

int notmain ( void ) {

	aes_context aes;

	unsigned char key[16];
	unsigned char iv_enc[16];
        unsigned char iv_dec[16];
        unsigned char input [16];
	unsigned char ct[16];
        unsigned char output [16];
        
        //Initialize UART connection
	init_uart();
        
        while(1) {
            
            //Ask KEY 
            serial_write(" KEY: ", 5);
            serial_read((char*)key, 16);
            serial_write((char*)key, 16);

            //Ask INITIAL VECTOR
            serial_write(" IV: ", 5);
            serial_read((char*)iv_enc, 16);
            serial_write((char*)iv_enc, 16);
            memcpy(iv_enc, iv_dec, 16);

            //Ask PLAINTEXT
            serial_write(" IN: ", 5);
            serial_read((char*)input, 16);
            serial_write((char*)input, 16);

            //Print Encrypted Text
            serial_write(" CT: ", 5);
            aes_setkey_enc( &aes, key, 128 );
            aes_crypt_cbc(&aes, AES_ENCRYPT, 16, iv_enc, input, ct);
            serial_write((char*)ct, 16);

            //Print Decrypted Text
            serial_write(" OUT: ", 6);
            aes_setkey_dec( &aes, key, 128 );
            aes_crypt_cbc(&aes, AES_DECRYPT, 16, iv_dec, ct, output);  
            serial_write((char*)output, 16);
        }
        
    return(0);

}