#include <lib/uart/uart.h>
#include <util/delay.h>
#include <stdio.h>

#define LED              PB0
#define LED_PORT         PORTB
#define LED_DDR          DDRB
#define BV(x)            (1 << x)
#define setBit(P, B)     P |= BV(B)
#define clearBit(P, B)   P &= ~BV(B)
#define toggleBit(P, B)  P ^= BV(B)

int main()
{
    setBit(LED_DDR, LED);
    UART_init();

    char buff[255];

    while(1) {
        int n_read = UART_gets(buff, 255);
        if (n_read > 0) {
            // send response
            int n_blinks = atoi(buff);
            for (int i = 0; i < n_blinks; i++) {
                setBit(LED_PORT, LED);
                _delay_ms(100);
                clearBit(LED_PORT, LED);
                if (i < n_blinks - 1) {
                    _delay_ms(200);
                }
            }
        }
        _delay_ms(500);
    }
}
