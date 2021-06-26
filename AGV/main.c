/*
 */

#include <avr/io.h>
#include <stdio.h>
#include "serial.h"
#include "util/delay.h"
#include <avr/interrupt.h>

#define stepper_DDR DDRK
#define stepper_port PORTK

#define forward 1
#define backward 2

struct stepper
{
    long int last_step;
    uint8_t time_profile;
    uint8_t direction;
    uint8_t step_pin;
    uint8_t dir_pin;
    uint16_t steps;
};

volatile long int ms;
volatile struct stepper stepper1;
volatile struct stepper stepper2;

void construct_stepper(volatile struct stepper *stepper, uint8_t step_pin, uint8_t dir_pin)
{
    stepper->last_step = ms;
    stepper->time_profile = 1;
    stepper->steps = 0;
    stepper->step_pin = step_pin;
    stepper->dir_pin = dir_pin;
    stepper->direction = 0;
}

void initialize_steppers()
{
    stepper_DDR |= 0xFF;//init all pins in bank C
}

void set_dir(volatile struct stepper *stepper)
{
    switch(stepper->direction)
    {
    case forward:
        stepper_port |= (1<<stepper->dir_pin);
        break;
    case backward:
        stepper_port &= ~(1<<stepper->dir_pin);
        break;
    default:
        break;
    }
}

void step(volatile struct stepper stepper)
{

            stepper_port |= (1<<stepper.step_pin);
            _delay_us(2);
            stepper_port &= ~(1<<stepper.step_pin);
            _delay_us(2);
}

void count_steps(volatile struct stepper *stepperino)
{
    switch(stepperino->direction)
        {
        case forward:
        stepperino->steps++;
        break;
        case backward:
        stepperino->steps--;
        break;
        default:
        break;
        }
}

void Handle_steps(volatile struct stepper *stepperino)
{
    if(stepperino->time_profile == 0)
    {

    }
    else if(ms >= (stepperino->last_step + stepperino->time_profile))
    {
        step(*stepperino);
        stepperino->last_step = ms;
        count_steps(stepperino);

    }
}

void turn(int16_t degrees, volatile struct stepper *stepperino1, volatile struct stepper *stepperino2)
{
    int16_t turn_steps = (float)(0.55)*degrees;
    struct stepper copy1 = *stepperino1;
    struct stepper copy2 = *stepperino2;

        stepperino1->time_profile = 10;
        stepperino1->steps = 0;
        stepperino2->time_profile = 10;
        stepperino2->steps = 0;

    if(turn_steps > 0)
    {
        stepperino1->direction = forward;
        stepperino2->direction = backward;
        set_dir(stepperino1);
        set_dir(stepperino2);

        while(stepperino1->steps <= (int)turn_steps)
        {
        Handle_steps(stepperino1);
        Handle_steps(stepperino2);
        }
    }

    if(turn_steps < 0)
    {
        turn_steps = abs(turn_steps);
        stepperino1->direction = backward;
        stepperino2->direction = forward;
        set_dir(stepperino1);
        set_dir(stepperino2);

        while(stepperino2->steps <= turn_steps)
        {
        //transmit_byte(turn_steps);
        Handle_steps(stepperino1);
        Handle_steps(stepperino2);
        }
    }
        *stepperino1 = copy1;
        *stepperino2 = copy2;
}

void init_stepper_timer0()
{
    TCCR0A |= (0<<WGM01) | (0<<WGM00);
    TCCR0B |= (0<<WGM02) | (1<<CS02) | (0<<CS01) | (0<<CS00);
    TIMSK0 |= (1<<TOIE0);
}

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
    stepper1.direction = forward;

    stepper1.time_profile = 3;
    stepper2.time_profile = 3;

    //turn(90, &stepper1, &stepper2);
    while(1)
    {
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



