#ifndef SONAR_H_INCLUDED
#define SONAR_H_INCLUDED

typedef struct sonar
{
    uint8_t echo_pin;
    uint8_t trigger_pin;
    uint16_t timerticks;
    uint32_t mM;
}sonar;

volatile sonar front_sonar;
volatile sonar left_sonar;
volatile sonar right_sonar;
volatile sonar back_sonar;

void init_sonar(sonar *sonar);
void trigger_sonar(sonar sonar);
void init_timer3();
void construct_sonar(sonar *sonar, uint8_t echo_pin, uint8_t trigger_pin);
void calculate_distance(sonar *sonar);


#endif // SONAR_H_INCLUDED
