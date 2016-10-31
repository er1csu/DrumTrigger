// Sound.c
#include "Sound.h"
#include "SoundSamples.h"
#include "../inc/tm4c123gh6pm.h"

long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
int soundArrayIndex = 0;



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
void Mono_Sound_Init() {
    // PB4, 5, 7 are SSI1 Output
    SYSCTL_RCGCGPIO_R |= 0x02;                  // Activate clock for Port B
    SYSCTL_RCGCSSI_R |= 0x04;                   // activate SSI2
    while((SYSCTL_PRGPIO_R & 0x02) == 0) {}     // Wait for ready
    GPIO_PORTB_DEN_R |= 0xB0;                   // Enable digital I/O F
    GPIO_PORTB_AFSEL_R |= 0xB0;                 // Enable the alt function
    GPIO_PORTB_AMSEL_R = 0;                     // 3) disable analog on PB
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0x0F00FFFF) | 0x20220000;    
    SSI2_CR1_R = 0x00000000;                    // disable SSI, master mode
    SSI2_CPSR_R = 8;                            // 20 MHz SSIClk 
    SSI2_CR0_R &= ~(0x0006FF30);    // SCR = 6, SPH = 1, SPO = 1
    SSI2_CR0_R |= 0x0F;             // DSS = 16-bit data
    SSI2_CR1_R |= 0x00000002;       // enable SSI
    
}

void DAC_Out(uint16_t code){   
    while((SSI2_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
    SSI2_DR_R = code; 
} 

// ***************** Timer0A_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq), 32 bits
// Outputs: none
void Timer0A_Init(uint32_t period){
    long sr;
    sr = StartCritical(); 
    SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
    TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
    TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
    TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
    TIMER0_TAILR_R = period-1;    // 4) reload value
    TIMER0_TAPR_R = 0;            // 5) bus clock resolution
    TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
    TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
    NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
    // interrupts enabled in the main program after all devices initialized
    // vector number 35, interrupt number 19
    NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
    TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
    EndCritical(sr);
}

void Timer0A_Handler(void){
    TIMER0_ICR_R = TIMER_ICR_TATOCINT; // acknowledge timer0A timeout
    DAC_Out(Bassoon64[soundArrayIndex]);
    soundArrayIndex = (soundArrayIndex+1)%64; 
}
