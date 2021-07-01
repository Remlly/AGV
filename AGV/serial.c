
#include "serial.h"

void USART_Init( unsigned int ubrr)
{
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /*Enable receiver and transmitter */
    UCSR0B |= (1<<RXEN0);
    UCSR0B |= (1<<TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1<<UCSZ01)|(3<<UCSZ00);
}


uint8_t recieve_Byte(void)
{
    loop_until_bit_is_set(UCSR0A, RXC0);
    {
     return UDR0;
    }
    /*else
    {
        return -1;
    }*/
}

void transmit_byte(uint8_t byte)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = byte;
}

void print_int32(int32_t byte)
{
    transmit_byte((byte/1000)%10);
    transmit_byte((byte/100)%10);
    transmit_byte((byte/10)%10);
    transmit_byte((byte%10));
    transmit_byte(0xA5);
}



void recieve_string(char code[])
{
    //code ontworpen voor een GPS module. dollar teken is begin van de string. kan wel gebruikt worden voor het onvangen van complexe instructies.
    char byte = recieve_Byte();
    if(byte == '$')
    {
        int x = 1;
        while(byte != '\n')
        {
            byte = recieve_Byte();
            code[x] = byte;
            x++;
        }
    }
}
