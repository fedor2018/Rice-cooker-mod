/*****************************************************************************
Flash used: 5222 of 32768 bytes (15.9 %). (Build Conf == Production)
SRAM used:   1564 of 4096 bytes (38.2 %).
http://www.element14.com/community/message/78621#78621/l/psoc-4-pioneer-kit-community-project023-tinyprintf-example
Not needed w/ tinyprintf // Linker flags added: -u _printf_float -u _scanf_float
MUST link in "m" library under Build Settings
*****************************************************************************/

#include "math.h"
#include "tinyprintf/API/printf.h"
#include <device.h>
#include "removeOffsetNoise.h"
#include "measurement.h"

#define CR 0x0D
#define LF 0x0A
#define NewLine() UART_UartPutChar(CR); UART_UartPutChar(LF); // CR+LF

void putdata ( void* p, char c)     // See printf.h for implementation
{
	UART_UartPutChar(c);            // function printf will utilize for output
}

int main()
{
    int16  iVref, iVtherm;   	// Vr resistor and thermistor
    uint32 iRes;                // Resistance of Thermistor
    uint16 iTemp;               // iTemp value in 100ths of a degree C
    uint16  Whole = 0;
    uint16  Fract = 0;
    char Out_String [30];    

	//Start hardware components
	ADC_Start();
	AMux_Start();
	UART_Start();               // 19.2K BAUD
    CyDelay(1000) ;
    CyGlobalIntEnable;          // Enable Global Interrupts
	init_printf(NULL, putdata); // initialize tinyprintf with PSoC putchar function
    UART_UartPutString("Thermistor Temperature \r");

	for(;;)
    {
    	iVtherm = MeasureResistorVoltage(AMUX_1_VT);		// Vr Thermistor
    	iVref = MeasureResistorVoltage(AMUX_1_VREF);		// Vr Resistor
	   	/* Use the thermistor component API function call to obtain the 
            temperature corresponding to the voltages measured */	
    	iRes = Thermistor_1_GetResistance(iVref, iVtherm);
    	iTemp = Thermistor_1_GetTemperature(iRes);
        Whole = iTemp / 100 ;
        Fract = iTemp - (Whole * 100);
        UART_UartPutString("Thermistor Temperature = ");
        printf("%d.", Whole); printf("%d", Fract) ; NewLine();

	    UART_UartPutString(Out_String); NewLine();

		CyDelay(1000);

    }
}

/* [] END OF FILE */
