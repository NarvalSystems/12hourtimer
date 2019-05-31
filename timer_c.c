/*
 * File:   timer_c.c
 * Author: Droidok
 *
 * Created on 2019. május 31., 11:59
 */
// PIC12F1822 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = HI        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), high trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
long ido;
int masodperc;
int perc;
int tizenketora;
void main(void) {
    OSCTUNEbits.TUN = 0b111111;//for frequency precision
    OSCCONbits.IRCF = 0b1100;//internal oscillator speed settings(125 khz)
    OSCCONbits.SCS = 0b10;//oscillator config-osc source(internal)
    TRISAbits.TRISA2 = 0;// a port tristate settings 0- output 1-input
    INTCONbits.GIE = 1;//global interrupt enable
    INTCONbits.PEIE =1;//peripherial interrupt enable 
    INTCONbits.T0IE =1;//timer0 iterrupt enable
    INTCONbits.T0IF = 0;//timer 0 interrupt flag
    OPTION_REGbits.T0CS = 0;//timer 0 clock source select
    OPTION_REGbits.PSA = 1;//prescaler assign
    OPTION_REGbits.PS = 0b000;//prescaler
    
    while(1)
    {
        
    }
    return;
}

void __interrupt () my_isr_routine (void) {//interrupt routine
    if(T0IE&&T0IF)
    {///// timer0 interrupt/////
        TMR0 = 23;//timer 0 count register reload
        
        ++masodperc;
        if(masodperc > 2000)
        {
            masodperc = 0;
            
            ++perc;
            if(perc > 60)
            {
                perc = 0;
                ++tizenketora;
                if(tizenketora>720)
                {
                    tizenketora = 0;
                    LATAbits.LATA2 ^=1;
                }
                else
                {
                    NOP();
                }
                
            }
            else
            {
                NOP();
            }
        }
        else
        {
            NOP();
        }
        T0IF = 0;//inerrupt flag clear
    }
}