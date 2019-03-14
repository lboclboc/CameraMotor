#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>


#define M1A             0
#define M2A             1
#define M1B             2
#define M2B             3
#define POWERBANK_PIN   4

#define M1      0
#define M2      1

// Timer settings.
#define COM0A_val 0 // Normal port operation, OC0A/OC0B disconnected.
#define COM0A1_val ((COM0A_val >> COM0A1) & 1)
#define COM0A0_val ((COM0A_val >> COM0A0) & 1)

#define COM0B_val 0 // Normal port operation, OC0A/OC0B disconnected.
#define COM0B1_val ((COM0B_val >> COM0B1) & 1)
#define COM0B0_val ((COM0B_val >> COM0B0) & 1)

#define WGM_val 2 // Clear Timer on Compare Match (CTC) Mode.
#define WGM02_val ((WGM_val >> WGM02) & 1)
#define WGM01_val ((WGM_val >> WGM01) & 1)
#define WGM00_val ((WGM_val >> WGM00) & 1)

#define POWERBANK_CYCLE 9000 // ms
#define POWERBANK_PULSE 700   // ms

// CLK divisor of 8 and OCRA0 11 -> 100us ticks.
#define OCRA0_COUNT 11
//#define TICKS 104462  // Ticks per step in order to make a 24h rotation.
#define TICKS 89932  // Ticks per step in order to make a 24h rotation.

//#define CS_val 5 // clk I/O /1024 (From prescaler).
//#define CS_val 3 // clk I/O /64 (From prescaler).
#define CS_val 2 // clk I/O /8 (From prescaler).
#define CS02_val ((CS_val >> CS02) & 1)
#define CS01_val ((CS_val >> CS01) & 1)
#define CS00_val ((CS_val >> CS00) & 1)

#define FOC0A_val 0 // No Compare Match
#define FOC0B_val 0 // No Compare Match

#define TOIE0_val 0 // Overflow Interrupt Enable

#define OCIE0A_val 1 // Timer/Counter0 Output Compare Match A Interrupt Enable
#define OCIE0B_val 0 // Timer/Counter0 Output Compare Match B Interrupt Enable

static unsigned char pos = 0;
static unsigned char pb_value;      // Value to use for the powerbank pin.

#define I_OFF {0,0}
#define I_FWD {1,0}
#define I_REV {0,1}

#if 1
unsigned char steps[4][2][2] = {
    {I_FWD, I_REV},
    {I_FWD, I_FWD},
    {I_REV, I_FWD},
    {I_REV, I_REV},
};
#else
unsigned char steps[8][2][2] = {
    {I_OFF, I_OFF},
    {I_FWD, I_OFF},
    {I_FWD, I_FWD},
    {I_OFF, I_FWD},
    {I_OFF, I_OFF},G
    {I_REV, I_OFF},
    {I_REV, I_REV},
    {I_OFF, I_REV},
};
#endif


unsigned char portb = 0;
unsigned short current = 0;
static void sleep(unsigned int);


void setup() {
    // All pins output.
    DDRB = 0x1F;
    
    // Timer 
    TCCR0A = (COM0A1_val << COM0A1) | (COM0A0_val << COM0A0) |
             (COM0B1_val << COM0B1) | (COM0B0_val << COM0B0) |
             (WGM01_val  << WGM01) | (WGM00_val  << WGM00);

    TCCR0B = (FOC0A_val << FOC0A) | (FOC0B_val << FOC0B) |
             (WGM02_val << WGM02) |
             (CS02_val  << CS02) | (CS01_val  << CS01) | (CS00_val  << CS00);

    TIMSK =  (OCIE0A_val << OCIE0A) | (OCIE0B_val << OCIE0B) | (TOIE0_val << TOIE0);

    OCR0A = OCRA0_COUNT;

    set_sleep_mode(SLEEP_MODE_IDLE);

    sei();
}

void update_motor() {
    unsigned char p = pos & ((sizeof steps / sizeof steps[0]) - 1);
    portb = (steps[p][M1][0] << M1A) | (steps[p][M1][1] << M1B) |
            (steps[p][M2][0] << M2A) | (steps[p][M2][1] << M2B);
    PORTB = portb;
    current = 4;
}

static void wait_char_p(unsigned char *p)
{
    cli();
    unsigned char org_value = *p;
    while(*p == org_value)
    {
        sleep_enable();
        sei();
        sleep_cpu();
        sleep_disable();
        cli();
        wdt_reset();
    }
    sei();
}

int main(int argc, char **argv)
{
    setup();
    while(1)
    {
        wait_char_p(&pos);
        update_motor();
        sleep(80);
        current = 3;
    }
}

void sleep(unsigned int ticks)
{
    while(ticks != 0) {
        sleep_enable();
        sleep_cpu();
        sleep_disable();
        ticks--;
        wdt_reset();
    }
}

void ms_tick()
{
    static unsigned int powerbank_clock = 0;
    if (++powerbank_clock > POWERBANK_CYCLE) {
        powerbank_clock = 0;
    }

    if (powerbank_clock < POWERBANK_PULSE) {
        pb_value = 1 << POWERBANK_PIN;
    }
    else {
        pb_value = 0;
    }
}

// Timer0 Interrupt 
ISR(TIMER0_COMPA_vect)
{
    static unsigned long tick = 0;
    static unsigned char pwm_step = 0;
    static unsigned int ms_prescaler = 0;

    if (++tick >= TICKS) {
        tick = 0;
        pwm_step = 0;
        pos--;
    }

    if (++ms_prescaler >= 10) {
        ms_prescaler = 0;
        ms_tick();
    }

    if (++pwm_step >= 4) {
        pwm_step = 0;
        PORTB = portb | pb_value;
    }

    if (pwm_step >= current) {
        PORTB = 0 | pb_value;
    }

}
