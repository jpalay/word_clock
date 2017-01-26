#include <avr/io.h>
#include <stdlib.h>

#include "ws2812_config.h"
#include "light_ws2812.h"

struct strand {
    struct cRGB *colors;
    uint16_t len;
};


struct strand *init_strand(uint16_t len);
void destroy_strand(struct strand *s);
void set_led_color(struct strand *s, uint16_t led, struct cRGB color);
void set_led(struct strand *s, uint16_t led);
void unset_led(struct strand *s, uint16_t led);
void set_multiple_leds(struct strand *s, uint16_t n);
void clear(struct strand *s);
void display(struct strand *s);
void display_rainbow(struct strand *s, uint8_t rainbow_pos, uint8_t step_size);
void wheel(uint8_t pos, struct cRGB* color);
