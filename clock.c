#include <lib/uart/uart.h>
#include <lib/ds3231/rtc.h>
#include <util/delay.h>
#include <stdio.h>

#define LED              PB0
#define LED_PORT         PORTB
#define LED_DDR          DDRB
#define BV(x)            (1 << x)
#define setBit(P, B)     P |= BV(B)
#define clearBit(P, B)   P &= ~BV(B)
#define toggleBit(P, B)  P ^= BV(B)
#define __AVR_ATmega328P__ 1

int main()
{
    _delay_ms(3000);
    UART_init();
    char buff[255];
    UART_puts("Initializing the rtc struct\n\r");

    /* struct tm t_init; */
    /* t_init.sec = 0; */
    /* t_init.min = 42; */
    /* t_init.hour = 12; */
    /* t_init.wday = 2; */
    /* t_init.mday = 16; */
    /* t_init.mon = 1; */
    /* t_init.year = 2017;   */

    UART_puts("Initializing the rtc device\n\r");
    twi_init_master();
    rtc_init();
    UART_puts("Setting the time\n\r");
    /* rtc_set_time(&t_init); */

    while(1) {
        struct tm *t = rtc_get_time();
        snprintf(buff, 255, "%d/%d/%d %d:%02d:%02d\n\r", t->mon, t->mday,
               t->year, t->hour, t->min, t->sec);
        UART_puts(buff);
        _delay_ms(1000);
    }
    
    return 0;
}
