/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>

void main()
{

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    #if(RELEASE == VERSION)
    {
        System_Init();
        PowerOn_to_Stop();
        
        while(1)
        {
            Command_Management();
            Get_ADCMeasureResult();
            Timing_Management();
 //           LowPower_Management();
            SeglcdDisplay(Get_CurrentMode(), Get_TimingCounterValue());
            
        }
    }
    #elif(SELFTEST == VERSION)
    {
        //System_Selftest();
    }
    #endif

}

/* [] END OF FILE */
