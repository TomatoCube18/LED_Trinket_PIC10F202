/* 
 * File:   Blink.c
 * Author: Percy
 *
 * Created on February 15, 2019, 8:06 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#pragma config WDTE = OFF
#pragma config CP = OFF
#pragma config MCLRE = OFF
#define _XTAL_FREQ 4000000

#define DEBOUNCE 10*1000/256    // switch debounce count = 10 ms/(256us/tick)

// DbnceHi()
//
// Debounce switch on given input pin
// Waits for switch input to be high continuously for DEBOUNCE*256/1000 ms
//
// Uses: TMR0       Assumes: TMR0 running at 256 us/tick
//
#define DbnceHi(PIN) TMR0 = 0;                  /* reset timer              */ \
                     while (TMR0 < DEBOUNCE)    /* wait until debounce time */ \
                         if (PIN == 0)          /*   if input low,          */ \
                             TMR0 = 0           /*     restart wait         */


/*
 * 
 */
int main(int argc, char** argv) {
    
    unsigned char state = 0;

    //*** Initialization
    // configure port
    
    // Bit 5 is zero to enable GP2 as output
    // Bit 6 is zero to enable pull up on GP3
    // Define all pins as output except  GP3
    
//    OPTION = 0b10011111;
    
    // configure wake-on-change and timer
    OPTION = 0b00000111;        // configure wake-up on change and Timer0:
             //0-------             enable wake-up on change (/GPWU = 0)
             //--0-----             timer mode (T0CS = 0)
             //----0---             prescaler assigned to Timer0 (PSA = 0)
             //-----111             prescale = 256 (PS = 111)
             //                     -> increment every 256 us
    
    TRIS=0b1000;                
    
    #define DataIn GP3
    
	//Loop Forever!
    for(;;){
            
        // test for wake-on-change reset    
            if (STATUSbits.GPWUF)       // if wake on change has occurred, 
            {                
                GPIO = 0x03;
                DbnceHi(DataIn);        //   wait for button to stop bouncing
            }

            // wait for button press
            GPIO = 0x03;
            while (DataIn == 1)         // wait until button low
            ;

            DbnceHi(DataIn);            // wait for stable button release
            state = 0;
            while (DataIn == 1)         // wait until button low
            {         
                switch(state)
                {
                    case 1:
                        GPIO = 0x01;
                        break;
                    case 51:
                        GPIO = 0x02;
                        break;
                    case 100:
                        state = 0;
                        break;
                }
                state += 1;
                __delay_ms(5);
            }
            
            DbnceHi(DataIn);            // wait for stable button release
            state = 0;
            while (DataIn == 1)         // wait until button low
            {
                switch(state)
                {
                    case 1:
                    case 40:
                    case 80:
                    case 120:
                        GPIO = 0x03;
                        break;
                    case 20:
                    case 60:
                    case 100:
                    case 140:
                        GPIO = 0x00;
                        break;
                    case 210:
                        state = 0;
                        break;
                }
                state += 1;
                __delay_ms(5);
            }
            
            DbnceHi(DataIn);            // wait for stable button release
            state = 0;
            while (DataIn == 1)         // wait until button low
            {
                switch(state)
                {
                    case 1:
                        GPIO = 0x03;
                        break;
                    case 20:
                        GPIO = 0x00;
                        break;
                    case 100:
                        state = 0;
                        break;
                }
                state += 1;
                __delay_ms(5);
            }
            
            // go into standby (low power) mode
            GPIO = 0x00;                   // turn off both LEDs

            DbnceHi(DataIn);            // wait for stable button release

            SLEEP();                    // enter sleep mode
            
            
            
    }

    return (EXIT_SUCCESS);
}

