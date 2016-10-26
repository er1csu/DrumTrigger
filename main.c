#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "Vibration.h"
#include "Pll.h"
#include "../inc/tm4c123gh6pm.h"

void SSR_Init(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void DelayWait10ms(uint32_t n);


int main(void){//uint32_t j; // main 1
    PLL_Init(Bus80MHz);                  // set system clock to 80 MHz
    InitVibrationSensors();
    
    while(1) {

    }

}
