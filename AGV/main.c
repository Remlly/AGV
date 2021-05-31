/*
 */

#include <avr/io.h>
#include <stdio.h>

#include "util/delay.h"
#include <avr/interrupt.h>

#include "stepper.h"
#include "serial.h"


int main(void)
{
    ///initializing stepper motors///


    construct_stepper(&stepper1, PK0, PK1);
    construct_stepper(&stepper2, PK2, PK3);
    initialize_steppers();
    init_stepper_timer();
    sei();

    ///initializing serial coms
    USART_Init(MYUBRR);


    while(1)
    {

    }
    ;

    return 0;
}


