
/***************************************************************************
#
#  A simple DC motor controller
#
#  This program implements the following functions:
#
#   a) startup throttle limit checks
#   b) read the throttle and set the PWM duty cycle
#
#  It should also check:
#
#   c) the maximum allowed motor current
#   d) low battery voltage
#   e) low battery voltage
#
#  but these checks (c,d,e) are not implemented yet.
#
#  Chip type           : ATmega8-16
#  Clock frequency     : 8.00 MHz
#
***************************************************************************/

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#define ADC_VREF_TYPE     0x40

unsigned char pwx;    // pulse width
unsigned char j = 0;  // LED value
unsigned char i = 0;  // loop counter


// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
    ADMUX = adc_input | (ADC_VREF_TYPE & 0xff);
    // Start the AD conversion
    ADCSRA |= 0x40;
    // Wait for the AD conversion to complete
    while ((ADCSRA & 0x10) == 0);
    ADCSRA |= 0x10;
    return ADCW;
}


// Timer 1 overflow interrupt service routine
ISR (TIMER1_OVF_vect)
{
    OCR1AL = pwx;  // set the pulse width
}


int main(void)
{
    int throttle;

    // Port B initialization (not used)
    // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=Out Func0=Out
    // State7=T State6=T State5=T State4=T State3=T State2=T State1=0 State0=T
    PORTB = 0x00;
    DDRB  = 0x02;

    // Port C initialization (not used)
    // Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
    // State6=T State5=T State4=T State3=T State2=T State1=T State0=T
    PORTC = 0x00;
    DDRC  = 0x00;

    // Port D initialization (used for simple LED toggle)
    // Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In
    // State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T
    PORTD = 0x00;
    DDRD  = 0x04;

    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: Timer 0 Stopped
    TCCR0 = 0x00;
    TCNT0 = 0x00;

    // Timer/Counter 1 initialization
    //
    // TCCR1A
    // COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10
    //
    // TCCR1B
    // ICNC1  ICES1  ---–   WGM13  WGM12 CS12  CS11  CS10
    //
    // Clock source: System Clock
    // Clock value: 7372.800 kHz
    // Mode: Fast PWM top=03FFh
    // OC1A output: Non-Inv
    // OC1B output: Discon
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer 1 Overflow Interrupt: On
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: Off
    // Compare B Match Interrupt: Off
    TCCR1A = 0x82;
    TCCR1B = 0x19;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ICR1H  = 0x00;
    ICR1L  = 0x3F;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;

    // Timer/Counter 2 initialization
    // Clock source: System Clock
    // Clock value: Timer 2 Stopped
    // Mode: Normal top=FFh
    // OC2 output: Disconnected
    ASSR  = 0x00;
    TCCR2 = 0x00;
    TCNT2 = 0x00;
    OCR2  = 0x00;

    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    MCUCR = 0x00;

    // Timer(s)/Counter(s) Interrupt(s) initialization
    TIMSK = 0x04;

    // USART initialization
    // Communication Parameters: 8 Data, 1 Stop, No Parity
    // USART Receiver: On
    // USART Transmitter: On
    // USART Mode: Asynchronous
    // USART Baud rate: 115200 (Double Speed Mode)
    UCSRA = 0x02;
    UCSRB = 0x18;
    UCSRC = 0x86;
    UBRRH = 0x00;
    UBRRL = 0x07;

    // Analog Comparator initialization
    // Analog Comparator: Off
    // Analog Comparator Input Capture by Timer/Counter 1: Off
    ACSR  = 0x80;
    SFIOR = 0x00;

    // ADC initialization
    // ADC Clock frequency: 230.400 kHz
    // ADC Voltage Reference: AVCC pin
    ADMUX  = ADC_VREF_TYPE & 0xff;
    ADCSRA = 0x85;

    // Global enable interrupts
    sei();

    while (1) {

        // read the throttle position
        throttle = read_adc(0);

        // toggle the LED
        if (i == 255) {
            i = 0;
            j = j ^ 0xff;
            PORTD = j;
        }
        i++;

        // If the ADC reads out of normal range then assume that the
        // throttle is either disconnected, or not connected properly
        if ((throttle < 100) || (throttle > 1000)) {
            // disable the PWM output
            // and cut the throttle
            TCCR1A = 0x02;
            throttle = 0;
        } else {


            if (throttle < 200) {
                // disable the PWM output
                // and cut the throttle
                TCCR1A = 0x02;
                throttle = 0;
            } else {
                // enable the PWM output
                // subtract the lower dead zone and then
                // multiply by 1.5x and then clip
                TCCR1A = 0x82;
                throttle -= 180;
                throttle = throttle + (throttle >> 1);
            }
            if (throttle > 1023) throttle = 1023;
        }
        pwx = throttle >> 4;
    }
}
