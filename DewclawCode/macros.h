#ifndef GENERAL_MACROS_H

#ifndef TRUE
// TRUE bool
#define TRUE 0x01
#endif

#ifndef FALSE
// FALSE bool
#define FALSE 0x00
#endif

// Macro for checking if a bit is set
#ifndef IS_BIT_SET
#define BIT_IS_SET(byte, bit) ((byte & (1 << bit)) != 0)
#endif

// Macro for checking if a bit is clear
#ifndef BIT_IS_CLEAR
#define BIT_IS_CLEAR(byte, bit) ((byte & (1 << bit)) == 0)
#endif

// Macro for setting a bit
#ifndef SET_BIT
#define SET_BIT(byte, bit) (byte |= (1 << bit))
#endif

// Macro for clearing a bit
#ifndef CLEAR_BIT
#define CLEAR_BIT(byte, bit) (byte &= ~(1 << bit))
#endif

// Macro for toggling a bit
#ifndef TOGGLE_BIT
#define TOGGLE_BIT(byte, bit) (byte ^= (1 << bit))
#endif

// Macro for setting a bit to a value
#ifndef SET_BIT_TO
#define SET_BIT_TO(byte, bit, value) (value ? SET_BIT(byte, bit) : CLEAR_BIT(byte, bit))
#endif

// Macro for getting the value of a bit
#ifndef GET_BIT
#define GET_BIT(byte, bit) ((byte & (1 << bit)) >> bit)
#endif

// Macro for setting pin to input
#ifndef SET_PIN_IN
#define SET_PIN_IN(byte, bit) (byte &= ~(1 << bit))
#endif

// Macro for setting pin to input with pullup
#ifndef SET_PIN_IN_PULLUP
#define SET_PIN_IN_PULLUP(byte, bit) (byte |= (1 << bit))
#endif

// Macro for setting pin to output
#ifndef SET_PIN_OUT
#define SET_PIN_OUT(byte, bit) (byte |= (1 << bit))
#endif

#ifndef ADC_PRESCALER_2
#define ADC_PRESCALER_2 0b000
#endif

#ifndef ADC_PRESCALER_4
#define ADC_PRESCALER_4 0b010
#endif

#ifndef ADC_PRESCALER_8
#define ADC_PRESCALER_8 0b011
#endif

#ifndef ADC_PRESCALER_16
#define ADC_PRESCALER_16 0b100
#endif

#ifndef ADC_PRESCALER_32
#define ADC_PRESCALER_32 0b101
#endif

#ifndef ADC_PRESCALER_64
#define ADC_PRESCALER_64 0b110
#endif

#ifndef ADC_PRESCALER_128
#define ADC_PRESCALER_128 0b111
#endif

#ifndef ADC_CHANNEL_ADC0
#define ADC_CHANNEL_ADC0 0b0000
#endif

#ifndef ADC_CHANNEL_ADC1
#define ADC_CHANNEL_ADC1 0b0001
#endif

#ifndef ADC_CHANNEL_ADC2
#define ADC_CHANNEL_ADC2 0b0010
#endif

#ifndef ADC_CHANNEL_ADC3
#define ADC_CHANNEL_ADC3 0b0011
#endif

#ifndef ADC_CHANNEL_ADC4
#define ADC_CHANNEL_ADC4 0b0100
#endif

#ifndef ADC_CHANNEL_ADC5
#define ADC_CHANNEL_ADC5 0b0101
#endif

#ifndef ADC_CHANNEL_ADC6
#define ADC_CHANNEL_ADC6 0b0110
#endif

#ifndef ADC_CHANNEL_ADC7
#define ADC_CHANNEL_ADC7 0b0111
#endif

#ifndef ADC_CHANNEL_TEMP_SENSOR
#define ADC_CHANNEL_TEMP_SENSOR 0b1000
#endif

#ifndef ADC_CHANNEL_1V1
#define ADC_CHANNEL_1V1 0b1110
#endif

#ifndef ADC_CHANNEL_GND
#define ADC_CHANNEL_GND 0b1111
#endif

#ifndef ADC_REF_AREF
#define ADC_REF_AREF 0b00
#endif

#ifndef ADC_REF_AVCC
#define ADC_REF_AVCC 0b01
#endif

#ifndef ADC_REF_1V1
#define ADC_REF_1V1 0b11
#endif

#ifndef ADC_LEFT_ADJUST
#define ADC_LEFT_ADJUST 0b1
#endif

#ifndef ADC_RIGHT_ADJUST
#define ADC_RIGHT_ADJUST 0b0
#endif

#ifndef ADC_TRIGGER_FREE_RUNNING
#define ADC_TRIGGER_FREE_RUNNING 0b000
#endif

#ifndef ADC_TRIGGER_ANALOG_COMPARATOR
#define ADC_TRIGGER_ANALOG_COMPARATOR 0b001
#endif

#ifndef ADC_TRIGGER_EXT_INT0
#define ADC_TRIGGER_EXT_INT0 0b010
#endif

#ifndef ADC_TRIGGER_TIMER0_COMPARE_MATCH_A
#define ADC_TRIGGER_TIMER0_COMPARE_MATCH_A 0b011
#endif

#ifndef ADC_TRIGGER_TIMER0_OVERFLOW
#define ADC_TRIGGER_TIMER0_OVERFLOW 0b100
#endif

#ifndef ADC_TRIGGER_TIMER1_COMPARE_MATCH_B
#define ADC_TRIGGER_TIMER1_COMPARE_MATCH_B 0b101
#endif

#ifndef ADC_TRIGGER_TIMER1_OVERFLOW
#define ADC_TRIGGER_TIMER1_OVERFLOW 0b110
#endif

#ifndef ADC_TRIGGER_TIMER1_CAPTURE_EVENT
#define ADC_TRIGGER_TIMER1_CAPTURE_EVENT 0b111
#endif

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef TRUE
#define TRUE 0x01
#endif

#ifndef FALSE
#define FALSE 0x00
#endif

#ifndef NULL
#define NULL 0x00
#endif

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

#ifndef TOUPPER
#define TOUPPER(c) ((c) & ~0x20)
#endif

#ifndef TOLOWER
#define TOLOWER(c) ((c) | 0x20)
#endif

#ifndef bit
#define bit(x) (1UL << (x))
#endif

// function pointer type for the callback function
typedef void (*callback_t)(void);

#endif // GENERAL_MACROS_H