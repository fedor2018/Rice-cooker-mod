/******************************************************************************
* File Name: measurement.c
*  Version 2.0
*
* Description:
*  This file contains the function that is used to find the thermistor resistance.
* 
* Note:
*
********************************************************************************
* Copyright (2013), Cypress Semiconductor Corporation. All Rights Reserved.
********************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress)
* and is protected by and subject to worldwide patent protection (United
* States and foreign), United States copyright laws and international treaty
* provisions. Cypress hereby grants to licensee a personal, non-exclusive,
* non-transferable license to copy, use, modify, create derivative works of,
* and compile the Cypress Source Code and derivative works for the sole
* purpose of creating custom software in support of licensee product to be
* used only in conjunction with a Cypress integrated circuit as specified in
* the applicable agreement. Any reproduction, modification, translation,
* compilation, or representation of this software except as specified above 
* is prohibited without the express written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH 
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes without further notice to the 
* materials described herein. Cypress does not assume any liability arising out 
* of the application or use of any product or circuit described herein. Cypress 
* does not authorize its products for use as critical components in life-support 
* systems where a malfunction or failure may reasonably be expected to result in 
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of 
* such use and in doing so indemnifies Cypress against all charges. 
*
* Use of this Software may be limited by and subject to the applicable Cypress
* software license agreement. 
*******************************************************************************/
#include "measurement.h"
#include "removeOffsetNoise.h"

/*******************************************************************************
*  Function Name: MeasureThermistorVoltage
********************************************************************************
* Summary:
* This functions returns the voltage across the resistor. Either Thermistor or Reference 
*
* Parameters:
* none
*
* Return: 
* resistor voltage in ADC counts

* Theory:
* Measure voltage across the resistor. Subtract offset from value, and filter value
*
* Side Effects:
* None
*******************************************************************************/
int32 MeasureResistorVoltage(uint8 channel)
{
	/* Voltage across resistor*/
	int32 result;
	
	/* Offset Voltage*/
	int32 offset;

	/* Select correct AMUX channel*/	
	AMux_FastSelect(channel);
	
	/* Read voltage across  resistor*/
    ADC_StartConvert();
	
	ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
	result = ADC_GetResult16(0);
	
	ADC_StopConvert();
	
	/* Get the offset voltage*/
	offset = GetOffset(); 
	
	/* Get CDS difference*/
	result = result - offset;
	
	/* Filter signal*/
	result = FilterSignal(result, channel);
	
	return result;
	
}
