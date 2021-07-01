/*
 */

#include <avr/io.h>
#include <stdio.h>
#include "serial.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#include "stepper.h"

int main(void)
{
    ///initializing stepper motors///
    construct_stepper(&stepper1, PK0, PK1);
    construct_stepper(&stepper2, PK2, PK3);
    initialize_steppers();
    init_stepper_timer0();
    sei();

    ///initializing serial coms
    USART_Init(MYUBRR);

    stepper2.direction = forward;
    stepper1.direction = backward;
    stepper1.time_profile = 10;
    stepper2.time_profile = 10;


    turn(360, &stepper1, &stepper2);
    while(1)
    {
        //


        Handle_steps(&stepper1);
        Handle_steps(&stepper2);
        set_dir(&stepper1);
        set_dir(&stepper2);

    }
    ;

    return 0;
}

ISR(TIMER0_OVF_vect)
{
    ms++;
}



