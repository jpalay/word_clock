#include "./lib/ds3231/rtc.h"

struct LED_word {
	uint16_t pos;
	uint16_t len;
};

void display_word(struct strand *s, struct LED_word w);
void undisplay_word(struct strand *s, struct LED_word w);
void iterate_words(struct strand *s);
struct LED_word hour_to_word(uint16_t i);
int past_or_to (uint16_t i);
void display_time(struct strand *s, struct tm *t);