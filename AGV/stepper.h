#ifndef STEPPER_H_INCLUDED
#define STEPPER_H_INCLUDED

#include <avr/io.h>
#include <stdio.h>


#define stepper_DDR DDRK
#define stepper_port PORTK

#define forward 1
#define backward 2

#define magic 4 //??????????????????????????????????????????


struct stepper
{
    long int last_step;
    uint8_t time_profile;
    uint8_t direction;
    uint8_t step_pin;
    uint8_t dir_pin;
    int16_t steps;
};

volatile long int ms;
volatile struct stepper stepper1;
volatile struct stepper stepper2;

void construct_stepper(volatile struct stepper *stepper, uint8_t step_pin, uint8_t dir_pin);
void initialize_steppers();
void set_dir(volatile struct stepper *stepper);
void static step(struct stepper stepper);
void static count_steps(volatile struct stepper *stepperino);
void Handle_steps(volatile struct stepper *stepperino);
void turn(int16_t degrees, volatile struct stepper *stepperino1, volatile struct stepper *stepperino2);
void init_stepper_timer0();

#endif // STEPPER_H_INCLUDED
