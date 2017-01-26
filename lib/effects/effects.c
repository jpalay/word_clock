#include <avr/io.h>
#include <util/delay.h>

#include "./lib/ws2812/strand.h"
#include "./lib/words/words.h"

void shifting_rainbow_200(struct strand *s) {
	uint8_t pos = 0;
    while (1) {
        display_rainbow(s, pos, 2);
        pos = (pos + 1) % 128;
        _delay_ms(200);
    }
}

void shifting_rainbow_50(struct strand *s) {
	uint8_t pos = 0;
    while (1) {
        display_rainbow(s, pos, 2);
        pos = (pos + 1) % 128;
        _delay_ms(50);
    }
}

void shifting_rainbow_10(struct strand *s) {
	uint8_t pos = 0;
    while (1) {
        display_rainbow(s, pos, 2);
        pos = (pos + 1) % 128;
        _delay_ms(10);
    }
}

void blink(struct strand *s, uint16_t n, bool repeat) {
	while (1) {
	    set_led(s, 0);
	    display(s);
	    _delay_ms(5);
	    for (int i = 1; i < n; i++) {
	    	unset_led(s, i-1);
	    	set_led(s, i);
	    	display(s);
	    	_delay_ms(5);
	    }
	    unset_led(s, n-1);
	    display(s);
	    if (!repeat) { break; }
	}
}

void fill(struct strand *s, uint16_t n) {
    for (int i = 0; i < n; i++) {
    	set_led(s, i);
    	display(s);
    	_delay_ms(10);
    }
}