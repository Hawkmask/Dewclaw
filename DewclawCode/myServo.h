#pragma once
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "macros.h"
#define SERVO_SWEEP_DELAY_MICRO 10 // 5 microseconds

class Servo
{
    public:
    uint16_t refresh;
    uint16_t min;
    uint16_t max;
    uint16_t position;
    uint8_t port;
    uint8_t pin;
    uint8_t ddr;
    
    void initServo(uint8_t pin, uint8_t ddr, uint8_t port );
    int setServo(uint16_t position);
    int sweepServo(uint16_t point1, uint16_t point2, uint16_t step);

    private:
    int validServoPosition(uint16_t position);
   
};
 
void Servo::initServo(uint8_t pin, uint8_t ddr, uint8_t port ) {
    // Set the timer1 control registers
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << WGM11);
    TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS10);
    ICR1 = F_CLK / refresh;

    // Default to the middle of the servo range
    OCR1A = (max + min) / 2;

    // Set the data direction registers
    SET_PIN_OUT(ddr, pin);
}

int Servo::setServo(uint16_t position) {
    // Check if the position is within the servo range
    if (!validServoPosition(position)) {
        return FALSE;
    }

    // Set the output compare registers
    OCR1A = position;

    return TRUE;
}

int Servo::validServoPosition(uint16_t position) {
    // Check if the position is within the servo range
    if (position > max || position < min) {
        return FALSE;
    }

    return TRUE;
}
int Servo::sweepServo(uint16_t point1, uint16_t point2, uint16_t step) {
    if (point1 > point2) {
        for (uint16_t i = point1; i >= point2; i -= step) {
            setServo(i);
            _delay_us(SERVO_SWEEP_DELAY_MICRO);
            TOGGLE_BIT(port, pin);
        }
    } else {
        for (uint16_t i = point1; i <= point2; i += step) {
            setServo(i);
            _delay_us(SERVO_SWEEP_DELAY_MICRO);
            TOGGLE_BIT(port, pin);
        }
    }
    return 0;
}