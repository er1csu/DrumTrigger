// Buttons module
#include <stdint.h>
#include "ST7735.h"
#include "../inc/tm4c123gh6pm.h"


static void Init_Onboard_Button() {
    // Init onboard switch PF0, PF4, and PF1 LED heartbeat
    SYSCTL_RCGCGPIO_R |= 0x20;                  // Activate clock for Port F
    while((SYSCTL_PRGPIO_R & 0x20) == 0) {}     // Wait for ready
    GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
    GPIO_PORTF_CR_R = 0x13;           // allow changes to PF0, PF1, PF4
    // only PF0 needs to be unlocked, other bits can't be locked
    GPIO_PORTF_AFSEL_R &= ~0x13;  //     disable alt funct on PF0,1,4
    GPIO_PORTF_AMSEL_R &= ~0x13;        // 3) disable analog on PF
    GPIO_PORTF_DEN_R |= 0x13;           // Enable digital I/O
    GPIO_PORTF_PCTL_R &= ~0x000F000F;   // 4) PCTL GPIO on port F
    GPIO_PORTF_IBE_R &= ~0x11;                  // Do not interrupt both edges
    GPIO_PORTF_IEV_R &= ~0x11;                  // Enable interrupt event
    GPIO_PORTF_PUR_R |= 0x11;          // enable pull-down on PF0 and PF4
    GPIO_PORTF_DIR_R  &= ~0x10;        // PF0 and PF4 are input, PF1 is output
    GPIO_PORTF_IS_R &= ~0x11;         // Configure for edge triggering
    GPIO_PORTF_ICR_R &= ~0x11;
    GPIO_PORTF_IM_R |= 0x11;                    //  Arm interrupt on PF0, PF4

    NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
    NVIC_EN0_R = 0x40000000;
}


void GPIOPortF_Handler(void) {
    

}