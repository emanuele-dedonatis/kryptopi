kryptopi
========

Programming on the bare metal of a Raspberry Pi, this project is expected to yield a working AES implementation in C, accepting plaintexts from the onboard UART, and returning the corresponding ciphertext after the encryption on the same channel. 

## test_serial ##
Test for serial library:
* Read and store from serial
* Write to serial

## test_mct_cbc ##
Monte Carlo Test CBC 
[The Advanced Encryption Standard Algorithm Validation Suite ](http://csrc.nist.gov/groups/STM/cavp/documents/aes/AESAVS.pdf "AESAVS")

## test_mct_ebc ##
Monte Carlo Test EBC 
[The Advanced Encryption Standard Algorithm Validation Suite ](http://csrc.nist.gov/groups/STM/cavp/documents/aes/AESAVS.pdf "AESAVS")

## kryptopi ##
Main code folder

## kryptopi_pc ##
PC client for serial communication.
Use Processing2 [processing.org](https://www.processing.org/ "processing.org")

## SD ##
Bootloader files
[David Welch's repo](https://github.com/dwelch67/raspberrypi "dwelch67")
