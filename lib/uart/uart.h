#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>

#define BAUDRATE 9600
#define UBRR (F_CPU/(BAUDRATE*16L))-1

#define RECV_BUFFER_SIZE 128

 
void UART_init();
char UART_recv();
void UART_putc(char data);
void UART_puts(char *s);
int UART_gets(char *buf, int buf_len);
