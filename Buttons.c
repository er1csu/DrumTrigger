// Buttons module
#ifndef BUTTONS_INCLUDED
#define BUTTONS_INCLUDED
#include <stdint.h>
#include "ST7735.h"
#include "../inc/tm4c123gh6pm.h"
#include "SoundSamples.h"
#include "Sound.h"
int menuIndex = 0;
int changeFlag = 0;

void Init_Buttons() {
    // Init switch PB0, PB1, PB2 Input, rising edge interrupts
    
    SYSCTL_RCGCGPIO_R |= 0x02;                  // Activate clock for Port B
    while((SYSCTL_PRGPIO_R & 0x02) == 0) {}     // Wait for ready   
    GPIO_PORTB_IBE_R &= ~0x07;                  // Do not interrupt both edges
    GPIO_PORTB_IEV_R |= 0x07;                   // Rising edge
    GPIO_PORTB_PDR_R |= 0x07;                   // 
    GPIO_PORTB_DIR_R  &= ~0x07;                 // PB0,1,2 are inputs
    GPIO_PORTB_IS_R &= ~0x07;                   // We don't want level triggering
    GPIO_PORTB_ICR_R &= ~0x07;                  // Clear flags
    GPIO_PORTB_DEN_R |= 0x07;                   // Enable digital I/O F
    GPIO_PORTB_IM_R |= 0x07;                    // Arm interrupt on PB0, 1, 2
    NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFF0FFF)|0x00006000; // Priority 3 (4th highest)
    NVIC_EN0_R |= 0x02;     
}


void GPIOPortB_Handler(void) {
    if ((GPIO_PORTB_RIS_R & 0x01) == 0x01) { // PB0 pressed
        GPIO_PORTB_ICR_R = 0x01;
        menuIndex += 1;
        if (menuIndex > 6) {
            menuIndex = 6;
        }
        changeFlag = 1;
    }
    else if ((GPIO_PORTB_RIS_R & 0x02) == 0x02) {
        GPIO_PORTB_ICR_R = 0x02;
        menuIndex -= 1;
        if (menuIndex < 0) {
            menuIndex = 0;
        }
        changeFlag = 1;
    }
    else {
        GPIO_PORTB_ICR_R = 0x04;
        //soundToPlay = soundArray[menuIndex];
        playFlag = 1;
        TIMER1_CTL_R = 0x00000001;
    }
}
#endif
