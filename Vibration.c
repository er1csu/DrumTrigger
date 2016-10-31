// Vibration.c
#include <stdint.h>
#include "Vibration.h"
#include "ST7735.h"
#include "ADCSWTrigger.h"
#include "../inc/tm4c123gh6pm.h"

void Init_Vibration_Sensors() {
    // Init cylinderical vib sensors (Port E 2, 3, 4, 5)
    SYSCTL_RCGCGPIO_R |= 0x10;                  // Activate clock for Port E
    while((SYSCTL_PRGPIO_R & 0x10) == 0) {}     // Wait for ready
    GPIO_PORTE_DIR_R &= 0x03;                  // PE 2,3,4,5 are inputs
    GPIO_PORTE_IS_R &= 0x03;                   // Configure for edge triggering
    GPIO_PORTE_IBE_R &= 0x03;                  // Do not interrupt both edges
    GPIO_PORTE_IEV_R |= 0x3C;                   // rising edge
    GPIO_PORTE_PCTL_R = 0x0;
    GPIO_PORTE_AFSEL_R = 0x0;
    //GPIO_PORTE_PDR_R |= 0x3C;                   // Enable pull down resistor (input high when pushed)
    GPIO_PORTE_ICR_R = 0x3C;                    // Clear flag for 2,3,4,5
    GPIO_PORTE_IM_R |= 0x3C;                    // Arm interrupt on PE 2,3,4,5
    NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF0F) | 0x00000040; // priority 2 (3rd highest)
    NVIC_EN0_R |= 0x10;                         // Enable interrupt on port E
    
    // Init the flex sensor (Port F3)
//    ADC0_InitSWTriggerSeq3_Ch9();
//    SYSCTL_RCGCGPIO_R |= 0x20;                  // Activate clock for Port F
//    while((SYSCTL_PRGPIO_R & 0x20) == 0) {}     // Wait for ready
//    GPIO_PORTF_LOCK_R = 0x4C4F434B;             // 2) unlock GPIO Port F
//    // GPIO_PORTF_CR_R = 0x13;                     // allow changes to PF0, PF1, PF4
//    GPIO_PORTF_DIR_R &= ~0x08;
//    GPIO_PORTF_DEN_R |= 0x08;
//    GPIO_PORTF_AFSEL_R |= 0x08;
//    GPIO_PORTF_AMSEL_R |= 0x08;
       
}

void GPIOPortE_Handler(void) {
    if (GPIO_PORTE_RIS_R & 0x04) {
        
    }        
}
