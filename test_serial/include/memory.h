/*
 *  Implementation of main memory function
 *  since "string.h" library is not included
 */

typedef unsigned int size_t;

// Copies the values of num bytes from the location pointed by source 
// directly to the memory block pointed by destination.
void *memcpy(void *destination, const void *source, size_t num);

// Sets the first num bytes of the block of memory pointed by ptr 
// to the specified value (interpreted as an unsigned char).
void *memset(void *ptr, int value, size_t num);
