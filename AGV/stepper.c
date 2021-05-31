#include "stepper.h"
#include "util/delay.h"
#include <avr/interrupt.h>

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
        stepper_DDR |= (1<<stepper->step_pin);
        break;
    case 2:
        stepper_DDR &= ~(1<<stepper->step_pin);
        break;
    default:
        break;
    }
}

void step(struct stepper *stepper)
{
    stepper->steps++;
    stepper_DDR |= (1<<stepper->step_pin);
    _delay_ms(1);
    stepper_DDR &= ~(1<<stepper->step_pin);
    _delay_ms(1);
}



void init_stepper_timer()
{
    TCCR1A |= (0<<WGM11) | (1<<WGM10);
    TCCR1B |= (1<<WGM12) | (0<<WGM13) | (0<<CS12) | (1<<CS11) | (1<<CS10);
    TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B);

}

ISR(TIMER1_COMPA_vect)
{
    step(&stepper1);
    set_dir(&stepper1);
    OCR1A = stepper1.speed;

}

ISR(TIMER1_COMPB_vect)
{
    step(&stepper2);
    set_dir(&stepper2);
    OCR1B = stepper2.speed;
}
