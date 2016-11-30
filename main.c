#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "Vibration.h"
#include "Buttons.h"
#include "Sound.h"
//#include "SoundSamples.h"
#include "Pll.h"
#include "../inc/tm4c123gh6pm.h"
#include "SoundSamples.h"

void SSR_Init(void);
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
void DelayWait10ms(uint32_t n);

void Init_test(void) {
    SYSCTL_RCGCGPIO_R |= 0x02;                  // Activate clock for Port B
    while((SYSCTL_PRGPIO_R & 0x02) == 0) {}     // Wait for ready   
//    GPIO_PORTB_IBE_R &= ~0x07;                  // Do not interrupt both edges
//    GPIO_PORTB_IEV_R |= 0x07;                   // Rising edge
//    GPIO_PORTB_PDR_R |= 0x07;                   // 
    GPIO_PORTB_DIR_R  |= 0x01;                 // PB0 is output
    GPIO_PORTB_AFSEL_R = 0;
    GPIO_PORTB_PCTL_R = 0x0;
    //GPIO_PORTB_IS_R &= ~0x07;                   // We don't want level triggering
    //GPIO_PORTB_ICR_R &= ~0x07;                  // Clear flags
    GPIO_PORTB_DEN_R |= 0x01;                   // Enable digital I/O F
    //GPIO_PORTB_IM_R |= 0x07;                    // Arm interrupt on PB0, 1, 2
    //NVIC_PRI0_R = (NVIC_PRI0_R&0xFFFF0FFF)|0x00006000; // Priority 3 (4th highest)
    //NVIC_EN0_R |= 0x02;
}

const unsigned short arrow[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

};



int main(void) {
    PLL_Init(Bus80MHz);                  // set system clock to 80 MHz
    DisableInterrupts();
    Stereo_Sound_Init();
    //Init_Vibration_Sensors();
    Init_Buttons();  
//    //Mono_Sound_Init();  
    
    //Timer0A_Init(2841);
    Timer0A_Init(1813);
    Timer1A_Init(8000000);
 
ST7735_InitR(INITR_REDTAB);
    ST7735_FillScreen(ST7735_BLACK);
    ST7735_DrawBitmap(0,10,arrow,10,10);
    ST7735_DrawBitmap(0,20,arrow,10,10);
    ST7735_DrawBitmap(0,30,arrow,10,10);
          EnableInterrupts(); 
//    Init_test();
//    for (;;) {        
//       GPIO_PORTB_DATA_R ^= 0x01;                                                                         
//    }
    for (;;) {
//        if (changeFlag) {
//            changeFlag = 0;
//            ST7735_FillRect(0,0,10,80,ST7735_WHITE);
//            ST7735_DrawBitmap(0,10+10*menuIndex,arrow,10,10);
//        }
    }

}

