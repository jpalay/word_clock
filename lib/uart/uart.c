#include "uart.h"

volatile uint8_t recv_buffer_len = 0;
volatile char recv_buffer[RECV_BUFFER_SIZE];

// "Private" methods
void _clear_recv_buffer();

void UART_init(){
    UBRR0H = (unsigned char)((UBRR) >> 8);
    UBRR0L = (unsigned char) UBRR;

    // 9600-8-E-1
    // That is, baudrate of 9600bps
    // 8 databits
    // Even parity
    // 1 stopbit
    UCSR0B = (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // And enable interrupts
    UCSR0C = (3 << UCSZ00);

    _clear_recv_buffer();
    sei();
}
 
char UART_recv() {
    while(!(UCSR0A & (1<<RXC0)));
    return UDR0;
}
 
void UART_putc(char data) {
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}
 
void UART_puts(char *s) {
    while(*s != '\0'){
        UART_putc(*s);
        s++;
    }
}

void _clear_recv_buffer() {
    memset((char *) recv_buffer, 0, RECV_BUFFER_SIZE);
    recv_buffer_len = 0;
}

int UART_gets(char *buff, int buff_size) {
    if (buff_size < RECV_BUFFER_SIZE)
        return -1;
    if (recv_buffer_len == 0)
        return -2;
    if (recv_buffer[recv_buffer_len - 1] != '\r')
        return -3;

    memcpy(buff, (char *) recv_buffer, recv_buffer_len);
    buff[recv_buffer_len - 1] = 0;
    uint8_t ret_val = recv_buffer_len - 1;
    _clear_recv_buffer();
    return ret_val;
}

// Interrupt
ISR(USART_RX_vect)
{
    unsigned char data = UDR0;
    // Log the data
    if (recv_buffer_len < RECV_BUFFER_SIZE) {
        recv_buffer[recv_buffer_len] = data;
        recv_buffer_len ++;
    }

    // Check for error
    if((UCSR0A & ((1 << FE0) | (1 << DOR0) | (1 << UPE0))) == 0) {
        // Write the data back, writing a newline if the data
        // recieved is a carriage return
        if (data == '\r') {
            while(!(UCSR0A & (1<<UDRE0)));
            UDR0 = '\n';
        }
        while(!(UCSR0A & (1<<UDRE0)));
        UDR0 = data;
    }
}


