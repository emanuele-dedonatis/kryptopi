/*
 * Raspberry PI UART connection methods 
 */

// Initialize UART
int init_uart ( void );

// Write len bytes from *buff to serial
void serial_write(char *buff, int len);

// Read len bytes from serial and store in *buff
void serial_read(char *buff, int len);
