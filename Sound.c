// Sound.c
#include "Sound.h"
#include "SoundSamples.h"
#include "../inc/tm4c123gh6pm.h"

long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
int indexMe = 0;
int fakeIndex = 0;
int playFlag = 0;
int playXD = 0;


/* Initialize 12-bit DAC stereo.
 * Input: period
 * Output: none
 */
void Stereo_Sound_Init() {
  SYSCTL_RCGCSSI_R |= 0x02;       // activate SSI1
  SYSCTL_RCGCGPIO_R |= 0x08;      // activate port D
  while((SYSCTL_PRGPIO_R&0x08) == 0){};// ready?
  GPIO_PORTD_AFSEL_R |= 0x0B;     // enable alt funct on PD0, 1, 3
  GPIO_PORTD_DEN_R |= 0x0B;       // configure PD0, 1, 3 as SSI
  GPIO_PORTD_PCTL_R = (GPIO_PORTD_PCTL_R&0xFFFF0F00)+0x00002022;
  GPIO_PORTD_AMSEL_R = 0;         // disable analog functionality on PD
  SSI1_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI1_CPSR_R = 8;             // 20 MHz SSIClk 
  SSI1_CR0_R &= ~(0x0006FF30);    // SCR = 6, SPH = 1, SPO = 1
  SSI1_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI1_CR1_R |= 0x00000002;       // enable SSI
}

void Stereo_Out(uint16_t code) {
    while ((SSI1_SR_R&0x00000001)==0){};
    if (playFlag) {
        SSI1_DR_R = code;
    }
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

void Timer1A_Init(uint32_t period){
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER1         // user function
  TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = period-1;    // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear TIMER1A timeout flag
  TIMER1_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF)|0x00008000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 37, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
  //TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER1A
}

void Timer2_Init(unsigned long period){
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2         // user function
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

void Timer3_Init(unsigned long period){
  SYSCTL_RCGCTIMER_R |= 0x08;   // 0) activate TIMER3// user function
  TIMER3_CTL_R = 0x00000000;    // 1) disable TIMER3A during setup
  TIMER3_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER3_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER3_TAILR_R = period-1;    // 4) reload value
  TIMER3_TAPR_R = 0;            // 5) bus clock resolution
  TIMER3_ICR_R = 0x00000001;    // 6) clear TIMER3A timeout flag
  TIMER3_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 51, interrupt number 35
  NVIC_EN1_R = 1<<(35-32);      // 9) enable IRQ 35 in NVIC
  TIMER3_CTL_R = 0x00000001;    // 10) enable TIMER3A
}

void Timer2A_Handler(void){
  TIMER2_ICR_R = TIMER_ICR_TATOCINT;
  playXD = 0;
  TIMER2_CTL_R = 0;
}

void Timer3A_Handler(void){
    TIMER3_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER3A timeout
    Stereo_Out(clap[fakeIndex]);
    fakeIndex = (fakeIndex+1)%64;
}

void Timer1A_Handler(void) {
    TIMER1_ICR_R = TIMER_ICR_TATOCINT;
    playFlag = 0;
    TIMER1_CTL_R = 0;
}

void Timer0A_Handler(void){
    TIMER0_ICR_R = TIMER_ICR_TATOCINT; // acknowledge timer0A timeout
    Stereo_Out(clap[indexMe]);
    //Stereo_Out(Bassoon64[indexMe]);
    indexMe = (indexMe+1)%64; 
}
