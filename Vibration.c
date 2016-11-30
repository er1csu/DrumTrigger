// Vibration.c
#include <stdint.h>
#include "Vibration.h"
#include "ST7735.h"
#include "ADCSWTrigger.h"
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"

void Init_Vibration_Sensors() {
    // Init cylinderical vib sensors (Port E 2, 3)
    SYSCTL_RCGCGPIO_R |= 0x10;                  // Activate clock for Port E
    while((SYSCTL_PRGPIO_R & 0x10) == 0) {}     // Wait for ready    
    GPIO_PORTE_DIR_R &= ~0x04;                  // PE 2,3 are inputs
    GPIO_PORTE_IS_R &= ~0x04;                   // Configure for edge triggering
    GPIO_PORTE_IBE_R &= ~0x04;                  // Do not interrupt both edges
    GPIO_PORTE_IEV_R |= 0x04;                   // rising edge
    //GPIO_PORTE_PCTL_R = 0x0;
    //GPIO_PORTE_AFSEL_R = 0x0;
    GPIO_PORTE_PDR_R |= 0x04;                   // Enable pull down resistor (input high when pushed)
    GPIO_PORTE_ICR_R &= ~0x04;                    // Clear flag for 2,3
    GPIO_PORTE_IM_R |= 0x04;                    // Arm interrupt on PE 2,3
    GPIO_PORTE_DEN_R |= 0x04;
    NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF0F) | 0x00000040; // priority 2 (3rd highest)
    NVIC_EN0_R |= 0x10;                         // Enable interrupt on port E
   
       
}

void GPIOPortE_Handler(void) {
        GPIO_PORTE_ICR_R = 0x04;
        playFlag = 1;
        TIMER1_CTL_R = 0x00000001;
}
