#include "samd11.h"

#define LED_PIN 16

/* Memory segments */
extern uint32_t _sfixed;
extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
extern uint32_t _sstack;
extern uint32_t _estack;


/* Simple "sleep" function */
static void delay(int n)
{
    int i;

    for (;n >0; n--)
    {
        for (i=0;i<100;i++)
            __asm("nop");
    }
}


/* Main program */
int main(void)
{
    REG_PORT_DIR0 |= (1<<LED_PIN);
    while (1)
    {
        REG_PORT_OUT0 &= ~(1<<LED_PIN);
        delay(500);
        REG_PORT_OUT0 |= (1<<LED_PIN);
        delay(500);
    }
}


/* Device exception handlers */
__attribute__ ((section(".vectors")))
const DeviceVectors exception_table = {
        (void*) (&_estack),	/* Initial stack pointer */
        (void*) Reset_Handler,		
        (void*) (0UL),		/* NMI  */
        (void*) (0UL),          /* HardFault  */
        (void*) (0UL), 		/* Reserved */
        (void*) (0UL), 		/* Reserved */
        (void*) (0UL), 		/* Reserved */
        (void*) (0UL), 		/* Reserved */
        (void*) (0UL), 		/* Reserved */
        (void*) (0UL), 		/* Reserved */
        (void*) (0UL), 		/* Reserved */
        (void*) (0UL),		/* SVC  */
        (void*) (0UL),		/* Reserved */
        (void*) (0UL),		/* Reserved */
        (void*) (0UL),		/* PendSV  */
        (void*) (0UL),	        /* SysTick */
        (void*) (0UL),          /* Power Manager */
        (void*) (0UL),          /* System Control */
        (void*) (0UL),          /* Watchdog Timer */
        (void*) (0UL),          /* Real-Time Counter */
        (void*) (0UL),          /* External Interrupt Controller */
        (void*) (0UL),          /* Non-Volatile Memory Controller */
        (void*) (0UL),          /* Direct Memory Access Controller */
        (void*) (0UL),          /* Universal Serial Bus */
        (void*) (0UL),          /* Event System Interface */
        (void*) (0UL),          /* Serial Communication Interface 0 */
        (void*) (0UL),          /* Serial Communication Interface 1 */
        (void*) (0UL),     	/* Serial Communication Interface 2 */
        (void*) (0UL),          /* Timer Counter Control */
        (void*) (0UL),          /* Basic Timer Counter 0 */
        (void*) (0UL),          /* Basic Timer Counter 1 */
        (void*) (0UL),          /* Analog Digital Converter */
        (void*) (0UL),          /* Analog Comparators */
        (void*) (0UL),          /* Digital Analog Converter */
        (void*) (0UL)           /* Peripheral Touch Controller */
};


/* Reset Handler - this is what gets called when the chip boots */
void Reset_Handler(void)
{
        uint32_t *pSrc, *pDest;

        pSrc = &_etext;
        pDest = &_srelocate;

        if (pSrc != pDest) {
                for (; pDest < &_erelocate;) {
                        *pDest++ = *pSrc++;
                }
        }

        for (pDest = &_szero; pDest < &_ezero;) {
                *pDest++ = 0;
        }

        pSrc = (uint32_t *) & _sfixed;
        SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);

        main();
        while (1);
}

