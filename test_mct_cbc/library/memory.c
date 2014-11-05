typedef unsigned int size_t;

void *memcpy(void *destination, const void *source, size_t num){
        unsigned char* dst8 = (unsigned char*)destination;
        unsigned char* src8 = (unsigned char*)source;

        while (num--) {
                *dst8++ = *src8++;
        }
        return destination;
}

void *memset(void *ptr, int value, size_t num){
    unsigned char* p=ptr;
    while(num--)
        *p++ = (unsigned char)value;
    return ptr;
}