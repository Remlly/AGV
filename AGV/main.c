/*
 */

#include <avr/io.h>
#include <stdio.h>
#include "serial.h"
#include "util/delay.h"

struct stepper
{
    uint8_t speed;
    uint8_t pins[4];
    uint16_t steps;
};

void construct_stepper(struct stepper *stepper, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
{
    stepper->speed = 0;
    stepper->steps = 0;
    stepper->pins[0] = pin1;
    stepper->pins[1] = pin2;
    stepper->pins[2] = pin3;
    stepper->pins[3] = pin4;

}

void initialize_steppers()
{
    DDRC |= 0xFF;//init all pins in bank C
}

void step(struct stepper *stepper)
{
    stepper->steps++;
    for (int x = 0; x < 4; x++)
    {
      PORTC |= (1<<stepper->pins[x]);
      _delay_us(600);
      PORTC &= ~(1<<stepper->pins[x]);
      _delay_us(600);
    }
}

void reverse_step(struct stepper *stepper)
{
    stepper->steps--;
    for (int x = 3; x >= 0; x--)
    {
      PORTC |= (1<<stepper->pins[x]);
      _delay_us(600);
      PORTC &= ~(1<<stepper->pins[x]);
      _delay_us(600);
    }
}

void init_stepper_timer()
{

}

int main(void)
{
    ///initializing stepper motors///

    struct stepper stepper1;
    struct stepper stepper2;
    construct_stepper(&stepper1, PC0, PC1, PC2, PC3);
    construct_stepper(&stepper2, PC4, PC5, PC6, PC7);
    initialize_steppers();

    ///initializing serial coms
    USART_Init(MYUBRR);
    while(1)
    {
        reverse_step(&stepper1);

    }
    ;

    return 0;
}
