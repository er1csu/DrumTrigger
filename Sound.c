// Sound.c
#include "Sound.h"
#include "../inc/tm4c123gh6pm.h"

/* Initialize 12-bit DAC stereo.
 * Input: period
 * Output: none
 */
void Stereo_Sound_Init(uint32_t period) {
    // PD0,1,3 are SSI2 outputs
}

/* Initialize 12-bit mono.
 * Input: period
 * Output: none
 */
void Mono_Sound_Init(uint32_t data) {
    // PB4, 5, 7 are SSI1 Output
    GPIO_PORTB_AFSEL_R |= 0xB0;                 // Enable the alt function
    GPIO_PORTB_AMSEL_R = 0;                     // 3) disable analog on PB
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0x0F00FFFF) | 0x20220000; 
    SYSCTL_RCGCSSI_R |= 0x02;                   // activate SSI1
    SSI1_CR1_R = 0x00000000;                    // disable SSI, master mode
    SSI1_CPSR_R = 0x02;                         // 8 MHz SSIClk 
    SSI1_CR0_R &= ~(0x0000FF70);                // SCR = 0, SPH = 1, SPO = 0 
    SSI1_CR0_R |= 0x0F;                         // DSS = 16-bit data
    SSI1_DR_R = data;                           // load 'data' into transmit FIFO
    SSI1_CR1_R |= 0x00000002;                   // enable SSI
}