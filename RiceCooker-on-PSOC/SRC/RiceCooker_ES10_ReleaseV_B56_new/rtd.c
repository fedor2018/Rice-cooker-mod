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

/*******************************************************************************
* Function Name: RTD_RestoTemp
********************************************************************************
*
* Summary:
*  This function takes the resistance value of RTD as input and provides the temperature
*
* Parameters:  
* Res:  Resistance of RTD
*
* Return: 
*  float 
*
* Reentrant: 
*  Yes
*
*******************************************************************************/
float RTD_RestoTemp(float Res)
{
	float Temp;
	
	if(Res>100)
	{
		Temp = ((((RTD_a0 * Res + RTD_a1)*Res + RTD_a2)*Res + RTD_a3)*Res + RTD_a4) * Res + RTD_a5 ;						
	}
	
	else
	{
		Temp = ((((RTD_b0 * Res + RTD_b1)*Res + RTD_b2)*Res + RTD_b3)*Res + RTD_b4) * Res + RTD_b5 ;	
	}
	
	return Temp;

}

/* [] END OF FILE */
