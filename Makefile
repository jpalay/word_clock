F_CPU = 16000000
DEVICE = atmega328p

CC = avr-gcc
LIB = lib/light_ws2812.c lib/light_ws2812.h lib/ws2812_config.h 
CFLAGS = -g2 -I. -Os -Wall -mmcu=$(DEVICE) -DF_CPU=$(F_CPU)
CFLAGS += -DUART_RX0_BUFFER_SIZE=256 -DUART_TX0_BUFFER_SIZE=256

MAIN = blink

upload: build
	avrdude -p m328p -c usbtiny -U flash:w:$(MAIN).hex

build: deps 
	$(CC) $(CFLAGS) -o $(MAIN).out $(MAIN).c\
			lib/uart/uart.o\
			lib/ds3231/twi-lowlevel.o\
			lib/ds3231/twi.o\
			lib/ds3231/rtc.o\
			lib/ws2812/light_ws2812.o\
			lib/ws2812/strand.o\
			lib/words/words.o\
			lib/effects/effects.o &&\
		avr-objcopy -j .text -j .data -O ihex $(MAIN).out $(MAIN).hex

deps:
	$(CC) $(CFLAGS) -L./lib/uart/ -o lib/uart/uart.o -c lib/uart/uart.c &&\
	$(CC) $(CFLAGS) -L./lib/ds3231/ -o lib/ds3231/twi-lowlevel.o -c lib/ds3231/twi-lowlevel.c &&\
	$(CC) $(CFLAGS) -L./lib/ds3231/ -o lib/ds3231/twi.o -c lib/ds3231/twi.c &&\
	$(CC) $(CFLAGS) -L./lib/ds3231/ -o lib/ds3231/rtc.o -c lib/ds3231/rtc.c &&\
	$(CC) $(CFLAGS) -L./lib/ws2812/ -o lib/ws2812/light_ws2812.o -c lib/ws2812/light_ws2812.c &&\
	$(CC) $(CFLAGS) -L./lib/ws2812/ -o lib/ws2812/strand.o -c lib/ws2812/strand.c &&\
	$(CC) $(CFLAGS) -L./lib/words/ -o lib/words/words.o -c lib/words/words.c &&\
	$(CC) $(CFLAGS) -L./lib/effects/ -o lib/effects/effects.o -c lib/effects/effects.c
clean:
	rmtrash *.out > /dev/null && rmtrash *.hex > /dev/null
