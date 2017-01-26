#include <lib/uart/uart.h>
#include <lib/ds3231/rtc.h>
#include <util/delay.h>
#include <stdio.h>

#include <lib/ws2812/strand.h>
#include <lib/words/words.h>
#include <lib/effects/effects.h>

#define LED              PB0
#define LED_PORT         PORTB
#define LED_DDR          DDRB
#define BV(x)            (1 << x)
#define setBit(P, B)     P |= BV(B)
#define clearBit(P, B)   P &= ~BV(B)
#define toggleBit(P, B)  P ^= BV(B)
#define __AVR_ATmega328P__ 1


int main2() {
    setBit(LED_DDR, LED);
    uint16_t n_leds = 130;
    struct strand *s = init_strand(n_leds);
    iterate_words(s);
    return 0;
}

int main()
{
    UART_init();
    twi_init_master();
    rtc_init();
        
	// LED SETUP
	setBit(LED_DDR, LED);
	uint16_t n_leds = 130;
	struct strand *s = init_strand(n_leds);

    // INDICATOR LIGHTS ON STARTUP
    // set_multiple_leds(s, 130);
    // display(s);
    // _delay_ms(500);
    // clear(s);
    // CLOCK SETUP
    
    blink(s, 130, false);
    // fill(s, 130);
    clear(s);

    // UPDATE THE TIME EVERY SECOND
    while (1) {
        // get the current time
        struct tm *t = rtc_get_time();

        // DISPLAY THE TIME ON THE CLOCK (words.c)
        display_time(s, t);
        shifting_rainbow_50(s);
        _delay_ms(1000);
        clear(s);
    }
    
    return 0;
}

void rtc_initialize_time() {

    struct tm t_init;
    t_init.sec = 0;
    t_init.min = 42;
    t_init.hour = 12;
    t_init.wday = 2;
    t_init.mday = 16;
    t_init.mon = 1;
    t_init.year = 2017;  

    rtc_set_time(&t_init);

}
