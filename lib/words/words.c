#include <avr/io.h>
#include <util/delay.h>

#include "./lib/ws2812/strand.h"
#include "./lib/words/words.h"

#define LED              PB0
#define LED_PORT         PORTB
#define LED_DDR          DDRB
#define BV(x)            (1 << x)
#define setBit(P, B)     P |= BV(B)
#define clearBit(P, B)   P &= ~BV(B)
#define toggleBit(P, B)  P ^= BV(B)

const struct LED_word IS = {0, 2};
const struct LED_word IT = {3, 2};
const struct LED_word TEN = {6, 3};
const struct LED_word HALF = {9, 4};
const struct LED_word TWENTY = {13, 6};
const struct LED_word QUARTER = {19, 7};
const struct LED_word FIVE = {26, 4};
const struct LED_word MINUTES = {31, 7};
const struct LED_word TO = {39, 2};
const struct LED_word NATHAN = {41, 6};
const struct LED_word PAST = {48, 4};
const struct LED_word NUM1 = {52, 3};
const struct LED_word NUM2 = {55, 3};
const struct LED_word NUM11 = {58, 6};
const struct LED_word NUM5 = {65, 4};
const struct LED_word NUM4 = {69, 4};
const struct LED_word NUM3 = {73, 5};
const struct LED_word NUM6 = {78, 3};
const struct LED_word NUM7 = {81, 5};
const struct LED_word NUM8 = {86, 5};
const struct LED_word NUM12 = {91, 6};
const struct LED_word NUM10 = {97, 3};
const struct LED_word NUM9 = {100, 4};
const struct LED_word LEE = {106, 3};
const struct LED_word LOVE = {111, 4};
const struct LED_word OCLOCK = {117, 6};



void display_word(struct strand *s, struct LED_word w) {
	for (int i = w.pos; i < w.pos + w.len; i++) {
		set_led(s, i);
	}
}

void undisplay_word(struct strand *s, struct LED_word w) {
	for (int i = w.pos; i < w.pos + w.len; i++) {
		unset_led(s, i);
	} 
}

void iterate_words(struct strand *s) {
	uint16_t all_words_len = 26;

	const struct LED_word all_words[] = {
		IS,
		IT,
		TEN,
		HALF,
		TWENTY,
		QUARTER,
		FIVE,
		MINUTES,
		TO,
		NATHAN, // first_name
		PAST,
		NUM1,
		NUM2,
		NUM11,
		NUM5,
		NUM4,
		NUM3,
		NUM6,
		NUM7,
		NUM8,
		NUM12,
		NUM10,
		NUM9,
		LEE, // last_name
		LOVE,
		OCLOCK
	};

	for (int i = 0; i < all_words_len; i++) {
		display_word(s, all_words[i]);
		if (i > 0)
			undisplay_word(s, all_words[i - 1]);

		display(s);
		_delay_ms(1000);
	}
}

struct LED_word hour_to_word(uint16_t i) {
	i = i % 12;
	switch (i) {
		case 0:
			return NUM12;
		case 1:
			return NUM1;
		case 2:
			return NUM2;
		case 3:
			return NUM3;
		case 4:
			return NUM4;
		case 5:
			return NUM5;
		case 6:
			return NUM6;
		case 7:
			return NUM7;
		case 8:
			return NUM8;
		case 9:
			return NUM9;
		case 10:
			return NUM10;
		case 11:
			return NUM11;
		default:
			return LOVE;
	}
}

int past_or_to (uint16_t i) {
	if (i < 33) { return 0; }
	else { return 1; }
}

void display_time(struct strand *s, struct tm *t) {
	// CLEAR THE DISPLAY (strand.c)
	clear(s);
	// "IT IS..."
	display_word(s, IT);
	display_word(s, IS);
	
	// ...MINUTE WORDS...
	if ((t->min >= 3 && t->min < 7) || (t->min >= 23 && t->min < 27) || 
		     (t->min >= 33 && t->min < 37) || (t->min >= 53 && t->min < 57)) { 
		display_word(s, FIVE);
		display_word(s, MINUTES);
	}
	if ((t->min >= 7 && t->min < 13) || (t->min >= 47 && t->min < 53)) { 
		display_word(s, TEN);
		display_word(s, MINUTES);
	}
	if ((t->min >= 13 && t->min < 17) || (t->min >= 43 && t->min < 47)) { 
		display_word(s, QUARTER); 
		display_word(s, MINUTES);
	}
	if ((t->min >= 17 && t->min < 27) || (t->min >= 33 && t->min < 43)) { 
		display_word(s, TWENTY); 
		display_word(s, MINUTES);
	}
	if (t->min >= 27 && t->min < 33) { 
		display_word(s, HALF);
	}
	// else: ((t->min >= 0 && t->min < 3) || (t->min >= 57 && t->min <= 59)) 
	if ((t->min >= 0 && t->min < 3) || (t->min >= 57 && t->min <= 59)) { 
		display_word(s, OCLOCK); 
	}
	else {
		// ...PAST/TO...
		if (t->min < 33) { display_word(s, PAST); }
		else { display_word(s, TO); }
	}
	// ...HOUR WORDS...
	display_word(s, hour_to_word(t->hour + past_or_to(t->min)));
}

