/*
 */

#include <avr/io.h>
#include <stdio.h>

#include "util/delay.h"
#include <avr/interrupt.h>

#include "stepper.h"
#include "sonar.h"
#include "serial.h"


int main(void)
{
    ///initializing stepper motors///
    construct_stepper(&stepper1, PK0, PK1);
    construct_stepper(&stepper2, PK2, PK3);
    initialize_steppers();
    init_stepper_timer();

    ///initializing sonars///
    construct_sonar(&front_sonar, PB0, PB4);
    init_sonar(&front_sonar);

    init_timer3();
    ///initializing serial coms
    USART_Init(MYUBRR);


    sei();
    trigger_sonar(front_sonar);
    while(1)
    {

        //transmit_byte(1);

    }
    ;

    return 0;
}


