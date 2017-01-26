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

    uint16_t n_leds = 130;
    struct strand *s = init_strand(n_leds);

    uint16_t pos = 0;

    while (1) {
        for (int i = 0; i < n_leds; i++) {
            if (i == pos)
                set_led(s, i);
            else
                unset_led(s, i);
        }

        pos = (pos + 1) % n_leds;
        display(s);
        _delay_ms(50);
    }

    destroy_strand(s);
    return 0;
}
