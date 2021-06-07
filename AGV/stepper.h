#ifndef STEPPER_H_INCLUDED
#define STEPPER_H_INCLUDED

#include <avr/io.h>
#include <stdio.h>

#define stepper_DDR DDRK

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

void construct_stepper(struct stepper *stepper, uint8_t step_pin, uint8_t dir_pin);
void initialize_steppers();
void set_dir(struct stepper *stepper);
void step(struct stepper *stepper);
void init_stepper_timer();

#endif // STEPPER_H_INCLUDED
