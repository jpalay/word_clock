#include <avr/io.h>
#include <util/delay.h>

 #include "./lib/ws2812/strand.h"

#define LED              PB0
#define LED_PORT         PORTB
#define LED_DDR          DDRB
#define BV(x)            (1 << x)
#define setBit(P, B)     P |= BV(B)
#define clearBit(P, B)   P &= ~BV(B)
#define toggleBit(P, B)  P ^= BV(B)

int main() {
    // Set LED for output
    setBit(LED_DDR, LED);

    uint16_t n_leds = 2;
    struct strand *s = init_strand(n_leds);

    uint8_t pos = 0;
    while (1) {
        display_rainbow(s, pos, 20);
        pos = (pos + 1) % 128;
        _delay_ms(50);
    }

    destroy_strand(s);
    return 0;
}

/* int main() { */
/*     setBit(LED_DDR, LED); */
/*     uint16_t n_leds = 2; */
/*     struct strand *s = init_strand(n_leds); */
/*  */
/*     set_led(s, 1); */
/*  */
/*     display_rainbow(s, 0, 0); */
/* } */
