
extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

#define GPFSEL1 0x20200004
#define GPSET0  0x2020001C
#define GPCLR0  0x20200028
#define GPPUD       0x20200094
#define GPPUDCLK0   0x20200098

#define AUX_ENABLES     0x20215004		// Auxiliary enables
#define AUX_MU_IO_REG   0x20215040		// Mini Uart IO Data
#define AUX_MU_IER_REG  0x20215044		// Mini Uart Interrupt Enable
#define AUX_MU_IIR_REG  0x20215048		// Mini Uart Interrupt Identify
#define AUX_MU_LCR_REG  0x2021504C		// Mini Uart Line Control
#define AUX_MU_MCR_REG  0x20215050		// Mini Uart Line Control
#define AUX_MU_LSR_REG  0x20215054		// Mini Uart Line Control
#define AUX_MU_MSR_REG  0x20215058		// Mini Uart Modem Status
#define AUX_MU_SCRATCH  0x2021505C		// Mini Uart Scratch
#define AUX_MU_CNTL_REG 0x20215060		// Mini Uart Extra Control
#define AUX_MU_STAT_REG 0x20215064		// Mini Uart Extra Status
#define AUX_MU_BAUD_REG 0x20215068		// Mini Uart Baudrate

#define CHAR_RETURN		0x0D
#define CHAR_NEWLINE	0x0A

void put_word(char word) {
   	 while(1)
		{
	    	if(GET32(AUX_MU_LSR_REG)&0x20) break;
   		}
       	PUT32(AUX_MU_IO_REG,word);
}

int init_uart ( void )
{
    unsigned int ra;

    PUT32(AUX_ENABLES,1);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_CNTL_REG,0);
    PUT32(AUX_MU_LCR_REG,3);
    PUT32(AUX_MU_MCR_REG,0);
    PUT32(AUX_MU_IER_REG,0);
    PUT32(AUX_MU_IIR_REG,0xC6);
    PUT32(AUX_MU_BAUD_REG,270);

    ra=GET32(GPFSEL1);
    ra&=~(7<<12); //gpio14
    ra|=2<<12;    //alt5
    ra&=~(7<<15); //gpio15
    ra|=2<<15;    //alt5
    PUT32(GPFSEL1,ra);

    PUT32(GPPUD,0);
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,(1<<14)|(1<<15));
    for(ra=0;ra<150;ra++) dummy(ra);
    PUT32(GPPUDCLK0,0);

    PUT32(AUX_MU_CNTL_REG,3);
    
	//put_word(CHAR_RETURN);
	//put_word(CHAR_NEWLINE);
	
    return(0);
}

void serial_write(char *buff, int len)
{
	int i;

	for(i=0; i<len; i++){
		put_word(buff[i]);
	}
	//put_word(CHAR_RETURN);
	//put_word(CHAR_NEWLINE);
	return;
}

char get_word(void) {
	while(1)
    {
       if(GET32(AUX_MU_LSR_REG)&0x01) break;
    }
    
    return GET32(AUX_MU_IO_REG);
}

void serial_read(char *buff, int len)
{
    int i;

	for(i=0; i<len; i++){
		buff[i]=get_word();
	}
	
    return;
}
