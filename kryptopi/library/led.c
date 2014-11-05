
extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028


int ledOn(int gpio)
{
    unsigned int ra;
    int fsel;
    switch(gpio) {
        case 18: fsel = 24; break;
        case 17: fsel = 21; break;
        default: goto done;
    }

    ra=GET32(GPFSEL1);
    ra&=~(7<<fsel);
    ra|=1<<fsel;
    PUT32(GPFSEL1,ra);

    PUT32(GPSET0,1<<gpio);

    done: return(0);
}

int ledOff(int gpio)
{
    unsigned int ra;
    int fsel;
    switch(gpio) {
        case 18: fsel = 24; break;
        case 17: fsel = 21; break;
        default: goto done;
    }

    ra=GET32(GPFSEL1);
    ra&=~(7<<fsel);
    ra|=1<<fsel;
    PUT32(GPFSEL1,ra);

    PUT32(GPCLR0,1<<gpio);
    done: return(0);
}
