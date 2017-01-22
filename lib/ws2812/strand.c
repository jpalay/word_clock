#include "./strand.h"

struct strand *init_strand(uint16_t len) {
    struct strand *s = malloc(sizeof(struct strand));
    s->len = len;
    s->colors = malloc(len * sizeof(struct cRGB));

    struct cRGB off = {0, 0, 0};
    for (int i = 0; i < len; i++) {
        s->colors[i] = off;
    }

    return s;
}

void destroy_strand(struct strand *s) {
    free(s->colors);
    free(s);
}

void set_led_color(struct strand *s, uint16_t led, struct cRGB color) {
    // Fail silently because I don't know a better way to do it
    if (led >= s->len)
        return;
    
    s->colors[led] = color;
}

void set_led(struct strand *s, uint16_t led) {
    struct cRGB c = {127, 127, 127};
    set_led_color(s, led, c);
}

void unset_led(struct strand *s, uint16_t led) {
    struct cRGB c = {0, 0, 0};
    set_led_color(s, led, c);
}

void display(struct strand *s) {
    ws2812_setleds(s->colors, s->len);
}

void display_rainbow(struct strand *s, uint8_t rainbow_pos, uint8_t step_size) {
    struct cRGB new_colors[s->len];
    struct cRGB off = {0, 0, 0};

    for (int i = 0; i < s->len; i++) {
        struct cRGB c = s->colors[i];
        if (c.r + c.g + c.b > 0) {
            struct cRGB color;
            wheel(rainbow_pos, &color);
            rainbow_pos = (rainbow_pos + step_size) % 128;
            new_colors[i] = color;
        }

        else {
            new_colors[i] = off;
        }
    }

    ws2812_setleds(new_colors, s->len);
}

void wheel(uint8_t pos, struct cRGB* color) {
    if (pos > 126) {
        pos = pos % 128;
    } 

    uint8_t relative_pos;
    if (pos < 43) {
        relative_pos = pos;
        color->r = 126 - (relative_pos * 3);
        color->g = 0;
        color->b = relative_pos * 3;
    }

    else if (pos < 86) {
        relative_pos = pos - 43;
        color->r = 0;
        color->g = relative_pos * 3;
        color->b = 126 - (relative_pos * 3);
    }
    else {
        relative_pos = pos - 86;
        color->r = relative_pos * 3;
        color->g = 123 - (relative_pos * 3);
        color->b = 0;
    }
}

