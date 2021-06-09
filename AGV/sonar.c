
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "sonar.h"
#include "serial.h"

void construct_sonar(sonar *sonar, uint8_t echo_pin, uint8_t trigger_pin)
{
    sonar->echo_pin = echo_pin;
    sonar->trigger_pin = trigger_pin;
}

void init_sonar(sonar *sonar)
{
    PCICR |= (1<<PCIE0);
    PCMSK0 |= (1<<PCINT0);
    DDRB &= ~(1<<sonar->echo_pin);
    DDRB |= (1<<sonar->trigger_pin);
}


void init_timer3()
{
    TCCR3A |= (0<<WGM31) | (0<<WGM30);
    TCCR3B |= (0<<WGM32) | (0<<WGM33) | (0<<CS32) | (1<<CS31) | (1<<CS30);
}

void trigger_sonar(sonar sonar)
{
    TCNT4 = 0;
    PORTB |= (1<<sonar.trigger_pin);
    _delay_ms(1);
    PORTB &= ~(1<<sonar.trigger_pin);
    _delay_ms(1);
}

void calculate_distance(sonar *sonar)
{
    sonar->mM = (343000*1024*sonar->timerticks)/(2 * F_CPU);
}

ISR(PCINT0_vect)
{
    transmit_byte(2);
    if(bit_is_set(DDRB, front_sonar.echo_pin))
    {
        front_sonar.timerticks = TCNT4;
        trigger_sonar(front_sonar);
        transmit_byte(3);
    }
    if(bit_is_set(DDRB, back_sonar.echo_pin))
    {
        back_sonar.timerticks = TCNT4;
    }
    if(bit_is_set(DDRB, left_sonar.echo_pin))
    {
        left_sonar.timerticks = TCNT4;
    }
    if(bit_is_set(DDRB, right_sonar.echo_pin))
    {
        right_sonar.timerticks = TCNT4;
    }
}
