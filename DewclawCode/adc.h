#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "macros.h"

typedef struct {
    uint8_t auto_trigger : 1;
    uint8_t trigger_src : 3;
    uint8_t interrupt : 1;
    uint8_t prescaler : 3;
    uint8_t multiplex_enable : 1;
    uint8_t ref : 2;
    uint8_t left_adjust : 1;
    uint8_t channel : 4;
} adc_config_t;

uint8_t adc_has_data(void);
uint8_t adc_init(adc_config_t *config);
uint16_t adc_read(void);

uint8_t adc_has_data(void) {
    return (ADCSRA & _BV(ADIF));
}

uint8_t adc_init(adc_config_t *config) {
    ADCSRA = (config->auto_trigger << ADATE) | (config->interrupt << ADIE) | (config->prescaler << ADPS0);
    ADCSRB = (config->trigger_src << ADTS0) | (config->multiplex_enable << ACME);
    ADMUX = (config->ref << REFS0) | (config->left_adjust << ADLAR) | (config->channel << MUX0); // Set the ADC multiplexer register
    
    if (config->channel <= 5) {
        DIDR0 = _BV(config->channel); // Set the digital input disable register
    }

    ADCSRA |= _BV(ADEN) | _BV(ADSC); // Enable the ADC and start a conversion
    return SUCCESS;
}

uint16_t adc_read(void) {
    ADCSRA |= _BV(ADSC);  // Start the conversion
    while (!adc_has_data());    // Wait for the conversion to finish
    ADCSRA |= _BV(ADIF);  // Clear the interrupt flag

    // check the ADLAR bit in ADMUX to determine how to read the result
    if (ADMUX & _BV(ADLAR)) {
        return ADCH;
    }
    return ADC; // Return the result
}
