// Shows how to call an assembly routine with one parameter
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"

// The function is defined in delay.asm in same dir
// We just need to add a declaration here, the defination can be
// seperately linked
extern void my_delay_cycles(uint32_t);

#define out 1		// Bit number to output on

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	/* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
	CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

	while(1) {
		__R30 |= 0x1<<out;		// Set the GPIO pin to 1
		my_delay_cycles(1);
		__R30 &= ~(0x1<<out);	// Clear the GPIO pin
		my_delay_cycles(1);
	}
}
