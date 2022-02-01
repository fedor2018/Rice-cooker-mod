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
#ifndef RTD_H
#define RTD_H


/***************************************
*             API Constants
***************************************/
#define RTD_Min_Temp		-20
#define RTD_Max_Temp		150
#define RTD_a0		0
#define RTD_a1		0
#define RTD_a2		0
#define RTD_a3		1.035381E-05
#define RTD_a4		0.2349955
#define RTD_a5		-245.3411

#define RTD_b0		0
#define RTD_b1		0
#define RTD_b2		0
#define RTD_b3		9.843489E-06
#define RTD_b4		0.2361844
#define RTD_b5		-246.0279


/***************************************
*        Function Prototypes
***************************************/
float RTD_RestoTemp(float Res);

#endif
//[] END OF FILE
