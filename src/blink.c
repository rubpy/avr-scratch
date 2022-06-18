/**
 * blink.c - BLINK!
 *
 * This code causes an LED on your (AVR) microcontroller board to blink.
 * What else would you expect?
 */

#ifndef __AVR__
#error "This program only supports AVR targets"
#endif

#include <avr/io.h>
#include <util/delay.h>

/* -------------------------------------------------------------------------- */

/**
 * If your device does not belong to one of the common Arduino board families
 * (based on ATmega's: 328P, 168, 2560, 1280, 32U4 or 16U4), you must explicitly
 * define the port, and the pin (i.e., bit) of that port, where an LED is
 * connected.
 * The data direction register corresponding to that port is also required.
 */

// #define BLINK_LED_PORT PORTB
// #define BLINK_LED_PIN 5
// #define BLINK_LED_DDR DDRB

/**
 * Additionally, you can define the delay (in milliseconds) between individual
 * blinks of the LED, as well as the duration of a blink.
 *
 * By default, it is set to blink (for 1000 ms) every 3000 ms.
 */

// #define BLINK_LED_DELAY 3000
// #define BLINK_LED_TIME 1000

/* -------------------------------------------------------------------------- */

#if !defined(BLINK_LED_PORT) || !defined(BLINK_LED_PIN) || \
    !defined(BLINK_LED_DDR)

// If any of the required define's is missing, we try to determine the full set.
#undef BLINK_LED_PORT
#undef BLINK_LED_PIN
#undef BLINK_LED_DDR

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__) || \
    defined(__AVR_ATmega168__)
// Arduino Uno, Arduino Nano
#define BLINK_LED_PORT PORTB
#define BLINK_LED_PIN 5
#define BLINK_LED_DDR DDRB
#elif defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
// Arduino Mega
#define BLINK_LED_PORT PORTB
#define BLINK_LED_PIN 7
#define BLINK_LED_DDR DDRB
#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
// Arduino Leonardo
#define BLINK_LED_PORT PORTC
#define BLINK_LED_PIN 7
#define BLINK_LED_DDR DDRC
#else
// unable to determine how the indicator LED is wired
#error \
    "BLINK_LED_PORT/BLINK_LED_PIN/BLINK_LED_DDR is not defined, and could not be determined according to __AVR_Device__"
#endif

#endif

#ifndef BLINK_LED_DELAY
#define BLINK_LED_DELAY 3000
#endif

#ifndef BLINK_LED_TIME
#define BLINK_LED_TIME 1000
#endif

/**
 * For an easier understanding of the AVR internals, here's some of the macros
 * predefined for, e.g., ATmega328P:
 *
 *  // Compiler-defined (AVR-GCC)
 *  #define __AVR_ARCH__ 5
 *  #define __AVR_ATmega328P__
 *
 *  // Defined in <avr/sfr_defs.h>
 *  #define __SFR_OFFSET 0x20
 *  #define _SFR_IO8(io_addr) ((io_addr) + __SFR_OFFSET)
 *
 *  // Defined in <avr/iom328p.h>
 *  #define PORTB5 5
 *  #define DDRB _SFR_IO8(0x04)
 *  #define PORTB _SFR_IO8(0x05)
 *
 *  // Defined above
 *  #define BLINK_LED_DDR DDRB
 *  #define BLINK_LED_PORT PORTB
 *  #define BLINK_LED_PIN 5
 *
 */

/* -------------------------------------------------------------------------- */

int main(void) {
  /**
   * Configures Nth bit of DDRX (data direction register for port X) as output.
   *
   * Equivalent to:
   *   (*(volatile uint8_t *)(__SFR_OFFSET + DDRX)) |= (1 << N);
   * Compiles to:
   *   sbi DDRX, N
   */
  BLINK_LED_DDR |= (1 << BLINK_LED_PIN);

  for (;;) {
    /**
     * Sets Nth bit of PORTX.
     *
     * Equivalent to:
     *   (*(volatile uint8_t *)(__SFR_OFFSET + PORTX)) |= (1 << N);
     * Compiles to:
     *   sbi PORTX, N
     */
    BLINK_LED_PORT |= (1 << BLINK_LED_PIN);

    /**
     * Delays execution for N ms.
     *
     * Typically, it will use __builtin_avr_delay_cycles((F_CPU / 1e3) * __ms).
     * To delve deeper, see 'avr_expand_delay_cycles' (gcc/config/avr/avr.c)
     * in the GCC source code repository.
     */
    _delay_ms(BLINK_LED_TIME);

    /**
     * Clears Nth bit of PORTX.
     *
     * Equivalent to:
     *   (*(volatile uint8_t *)(__SFR_OFFSET + PORTX)) &= ~(1 << N);
     * Compiles to:
     *   cbi PORTX, N
     */
    BLINK_LED_PORT &= ~(1 << BLINK_LED_PIN);

    _delay_ms(BLINK_LED_DELAY);
  }

  return 0;
}
