#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "Vibration.h"
#include "Buttons.h"
#include "Sound.h"
#include "SoundSamples.h"
#include "Pll.h"
#include "../inc/tm4c123gh6pm.h"

void SSR_Init(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void DelayWait10ms(uint32_t n);


int main(void) {
    PLL_Init(Bus80MHz);                  // set system clock to 80 MHz
    Init_Vibration_Sensors();
    Init_Buttons();  
    //Mono_Sound_Init();  
    
    Timer0A_Init(2841);
    EnableInterrupts();
    
    for (;;) {        
        
    }

}
