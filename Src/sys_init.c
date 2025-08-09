#include "stm32f4xx.h"
void SystemInit (void)
{
	/*Enable float point hardware*/
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));
}
