/*
 */

#include <avr/io.h>
#include <stdio.h>
#include "serial.h"
#include "util/delay.h"
#include <avr/interrupt.h>

#define stepper_DDR DDRK
#define stepper_port PORTK

struct stepper
{
    uint8_t speed;
    uint8_t direction;
    uint8_t step_pin;
    uint8_t dir_pin;
    uint16_t steps;
};

volatile struct stepper stepper1;
volatile struct stepper stepper2;

void construct_stepper(struct stepper *stepper, uint8_t step_pin, uint8_t dir_pin)
{
    stepper->speed = 125;
    stepper->steps = 0;
    stepper->step_pin = step_pin;
    stepper->dir_pin = dir_pin;
    stepper->direction = 0;
}

void initialize_steppers()
{
    stepper_DDR |= 0xFF;//init all pins in bank C
}

void set_dir(struct stepper *stepper)
{
    switch(stepper->direction)
    {
    case 1:
        stepper_port |= (1<<stepper->step_pin);
        break;
    case 2:
        stepper_port &= ~(1<<stepper->step_pin);
        break;
    default:
        break;
    }
}

void step(struct stepper *stepper)
{
    stepper->steps++;
    stepper_port |= (1<<stepper->step_pin);
    _delay_ms(10);
    stepper_port &= ~(1<<stepper->step_pin);
    _delay_ms(10);
}



void init_stepper_timer()
{
    TCCR1A |= (0<<WGM11) | (1<<WGM10);
    TCCR1B |= (1<<WGM12) | (0<<WGM13) | (0<<CS12) | (1<<CS11) | (1<<CS10);
    TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B);

}

int main(void)
{
    ///initializing stepper motors///


    construct_stepper(&stepper1, PK0, PK1);
    construct_stepper(&stepper2, PK2, PK3);
    initialize_steppers();
    init_stepper_timer();
    //sei();

    ///initializing serial coms
    USART_Init(MYUBRR);

    set_dir(&stepper1);
    set_dir(&stepper2);
    while(1)
    {
        step(&stepper1);
    }
    ;

    return 0;
}

ISR(TIMER1_COMPA_vect)
{
    step(&stepper1);
    OCR1A = stepper1.speed;
}

ISR(TIMER1_COMPB_vect)
{
    step(&stepper2);
    OCR1B = stepper2.speed;
}
