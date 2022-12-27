#ifndef F_CPU
// 16 MHz clock speed
#define F_CPU 16000000UL
#endif

#ifndef F_CLK
// 16 MHz clock speed
#define F_CLK F_CPU
#endif

// Includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "myServo.h"
#include "macros.h"
#include "adc.h"

#define SERVO_REFRESH_RATE 333 // 333 Hz
// Max calculated as 0.8ms -> 35200 ticks, experimentally found to be ~35255 ticks for 0.8ms pulse
#define SERVO_MAX 35255
// Min calculated as 2.2ms -> 12800 ticks, experimentally found to be ~12880 ticks for 2.2ms pulse
#define SERVO_MIN 12880


// Functions
const uint8_t Xpin = 0;  // analog pin used to connect the 
const uint8_t Ypin = 1;  // analog pin used to connect the potentiometer
uint8_t flxVal;    // variable to read the value from the analog pin
uint8_t addVal;
Servo flx;
Servo add;

adc_config_t sense={
    .auto_trigger = 1,
    .trigger_src = 0,
    .interrupt = 0,//needs to be different mode to switch between two
    .prescaler = 0,
    .multiplex_enable = 1,
    .ref = 00,
    .left_adjust = 1,
    .channel = Xpin
  };

int main(void) {
    // Initialize servos
    flx.initServo(PD5,DDRD,PORTD);
    add.initServo(PD6,DDRD,PORTD);
    
    // Set PD5,6 to output
    SET_PIN_OUT(DDRD, PD5);
    SET_PIN_OUT(DDRD, PD6);
    
    // Set PD5,6 to low
    CLEAR_BIT(PORTD, PD5);
    CLEAR_BIT(PORTD, PD6);
    
    //adc initialize here
    adc_init(&sense);

    // Loop forever
    while (1) {
      //switch between reading x and y pin on adc for using multiple pins/having multiple sensor inputs
      
      flxVal = map(adc_read(), 0, 1023, 35255, 12880);
      flx.setServo(flxVal);
      add.setServo(flxVal);
    }
    return 0;
}
