#include "serial.h"
#include "aes.h"
#include "memory.h"
#include "led.h"


#define PKG_LEN 16
#define MAX_BUFF 1048576
#define END_CMD 0x24    // $: END TRASMISSION
#define ENC_CMD 0x45    // E: ENCRYPT MODE
#define DEC_CMD 0x44    // D: DECRYPT MODE

/* COMPARE A RECEIVED PACKAGE TO COMMAND FLAGS
 * Return 1 if each byte of input package 
 * is equal to a predefined command byte
 */
int equal(char*input, char cmd) {
    int i, equal=1;
    for(i=0; i<PKG_LEN; i++){
        if(input[i]==cmd){
            equal=1;
        }else{
            equal=0;
            goto ret;
        }
    }
    ret: return equal;
}

/*
 * LED COLOR LEGEND
 *      GREEN           Encrypting/Decrypting
 *      RED             Error
 *      GREEN + RED     Finished
 */
int notmain ( void ) {

	aes_context aes;
        
	unsigned char key[PKG_LEN];
	unsigned char iv[PKG_LEN];
        unsigned char input[PKG_LEN];
        int pkg_stored, mode=-1;
	unsigned char plaintext[MAX_BUFF];
	unsigned char ciphertext[MAX_BUFF];

        
	init_uart();
        
        // READ MODE
        // EEEEEEEEEEEEEEEE: Encrypt mode
        // DDDDDDDDDDDDDDDD: Decrypt mode
        serial_read((char*)input, PKG_LEN);
        if(equal((char*)input, ENC_CMD)){
            mode=AES_ENCRYPT;
        }else{
                if(equal((char*)input, DEC_CMD)){
                    mode=AES_DECRYPT;
                }else{
                    mode=-1;
                }
        }
        
        // READ KEY
        serial_read((char*)key, PKG_LEN);
        // READ IV
        serial_read((char*)iv, PKG_LEN);
        
        // READ INPUT TEXT
        serial_read((char*)input, PKG_LEN);
        pkg_stored=0;
        do{
            // control if there is space for the new package
            if((pkg_stored+1)*PKG_LEN>MAX_BUFF){
                ledOff(LED_GREEN);
                ledOn(LED_RED);
                goto finish;
            }
            // save received package
                memcpy(plaintext+(PKG_LEN*pkg_stored), input, PKG_LEN);
                pkg_stored++;
                serial_read((char*)input, PKG_LEN);
        }while(!equal((char*)input, END_CMD)); 
        // while is not end package: $$$$$$$$$$$$$$$$

        switch(mode) {
            case AES_ENCRYPT:  
                ledOn(LED_GREEN);
                aes_setkey_enc( &aes, key, 128 );
                aes_crypt_cbc(&aes, AES_ENCRYPT, (PKG_LEN*pkg_stored), iv, plaintext, ciphertext);
                ledOff(LED_GREEN);
                break;
            case AES_DECRYPT: 
                ledOn(LED_GREEN);
                aes_setkey_dec( &aes, key, 128 );
                aes_crypt_cbc(&aes, AES_DECRYPT, (PKG_LEN*pkg_stored), iv, plaintext, ciphertext);
                ledOff(LED_GREEN);
                break;
            default:
                goto finish;
        }

        serial_write((char*)ciphertext, (PKG_LEN*pkg_stored));
        ledOn(LED_RED);
        ledOn(LED_GREEN);
    
    finish: return(0);
}