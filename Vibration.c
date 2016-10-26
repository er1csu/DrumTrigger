// Vibration.c
#include <stdint.h>
#include "ST7735.h"
#include "../inc/tm4c123gh6pm.h"

void InitVibrationSensors() {
    // Initialize PB0 to use the vibration sensor
    SYSCTL_RCGCGPIO_R |= 0x02;                  // Activate clock for Port B
    while((SYSCTL_PRGPIO_R & 0x02) == 0) {}     // Wait for ready
    GPIO_PORTB_DIR_R &= ~0x03;                  // PB1 & PB0 are inputs
    GPIO_PORTB_IS_R &= ~0x03;                   // Configure for edge triggering
    GPIO_PORTB_IBE_R &= ~0x03;                  // Do not interrupt both edges
    GPIO_PORTB_IEV_R |= 0x03;                   // Enable interrupt event
    GPIO_PORTB_PCTL_R = 0x0;
    GPIO_PORTB_AFSEL_R = 0x0;
    GPIO_PORTB_PDR_R |= 0x03;                   // Enable pull down (input high when pushed)
    GPIO_PORTB_ICR_R = 0x03;                    // Clear flag for 0 and 1
    GPIO_PORTB_IM_R |= 0x03;                    // Arm interrupt on PB0,1
    NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFF00FF) | 0x0000A000; //priority 5
    NVIC_EN0_R = 0x02;                          // Enable interrupt 1 in NVIC
    GPIO_PORTB_DEN_R |= 0x01;                   // Enable PB0
}

void GPIOPortB_Handler(void) {
    GPIO_PORTB_ICR_R = 0x03;                     // Acknowledge flags
}
