#include <avr/io.h>
#include <util/delay.h>

#define LED              PC4
#define LED_PORT         PORTC
#define LED_DDR          DDRC
#define BV(x)            (1 << x)
#define setBit(P, B)     P |= BV(B)
#define clearBit(P, B)   P &= ~BV(B)
#define toggleBit(P, B)  P ^= BV(B)

int main() {
    setBit(LED_DDR, LED);
    while (1) {
        toggleBit(LED_PORT, LED);
        _delay_ms(500);
        toggleBit(LED_PORT, LED);
        _delay_ms(100);
    }
}
