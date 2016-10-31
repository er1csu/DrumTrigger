// Speaker module
#include <stdint.h>


// **************DAC_Init*********************

/* Initialize 12-bit DAC stereo.
 * Input: period
 * Output: none
 */
void Stereo_Sound_Init(uint32_t period);

/* Initialize 12-bit mono.
 * Input: period
 * Output: none
 */
void Mono_Sound_Init(void);


/* Output data to the DAC
 *
 */
void DAC_Out(uint16_t code);


void Timer0A_Init(uint32_t period);
