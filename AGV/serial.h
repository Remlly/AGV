#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#define BAUD 9600
#define FOSC F_CPU // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <util/setbaud.h>
#include <avr/io.h>

void USART_Init( unsigned int ubrr);
uint8_t recieve_Byte(void);
void transmit_byte(uint8_t byte);
void recieve_string(char code[]);
void print_int32(int32_t byte);

#endif // SERIAL_H_INCLUDED
