// Speaker module
#include <stdint.h>


// **************DAC_Init*********************

/* Initialize 12-bit DAC stereo.
 * Input: period
 * Output: none
 */
void Stereo_Sound_Init(void);

/* Initialize 12-bit mono.
 * Input: period
 * Output: none
 */
void Mono_Sound_Init(void);

extern int playFlag;
extern int playXD;
/* Output data to the DAC
 *
 */
void DAC_Out(uint16_t code);


void Timer0A_Init(uint32_t period);

void Timer1A_Init(uint32_t period);

void Timer2_Init(unsigned long period);

void Timer3_Init(unsigned long period);