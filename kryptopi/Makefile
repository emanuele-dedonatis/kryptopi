
ARMGNU ?= /usr/local/arm-cs-tools/bin/arm-none-eabi

CFLAGS = -I$(INCD)
LDFLAGS = -L$(LIBD)

COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 

INCD = ./include
LIBD = ./library

gcc : kryptopi.hex kryptopi.bin

all : gcc clang

clean :
	rm -f *.o
	rm -f ./library/*.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.opt.s

vectors.o : vectors.s
	$(ARMGNU)-as vectors.s -o vectors.o

kryptopi.o : kryptopi.c serial.o led.o aes.o memory.o
	$(ARMGNU)-gcc $(COPS) $(CFLAGS) -c kryptopi.c -o kryptopi.o

serial.o : $(LIBD)/serial.c $(INCD)/serial.h
	$(ARMGNU)-gcc $(COPS) -c $(LIBD)/serial.c -o $(LIBD)/serial.o

led.o : $(LIBD)/led.c $(INCD)/led.h
	$(ARMGNU)-gcc $(COPS) -c $(LIBD)/led.c -o $(LIBD)/led.o
	
aes.o : $(LIBD)/aes.c $(INCD)/aes.h
	$(ARMGNU)-gcc $(COPS) $(CFLAGS) -c $(LIBD)/aes.c -o $(LIBD)/aes.o
	
memory.o : $(LIBD)/memory.c $(INCD)/memory.h
	$(ARMGNU)-gcc $(COPS) -c $(LIBD)/memory.c -o $(LIBD)/memory.o

kryptopi.elf : memmap vectors.o kryptopi.o serial.o aes.o memory.o
	$(ARMGNU)-ld vectors.o kryptopi.o $(LIBD)/serial.o $(LIBD)/aes.o $(LIBD)/memory.o $(LIBD)/led.o -T memmap -o kryptopi.elf
	$(ARMGNU)-objdump -D kryptopi.elf > kryptopi.list

kryptopi.bin : kryptopi.elf
	$(ARMGNU)-objcopy kryptopi.elf -O binary kryptopi.bin
	mv kryptopi.bin kernel.img

kryptopi.hex : kryptopi.elf
	$(ARMGNU)-objcopy kryptopi.elf -O ihex kryptopi.hex




