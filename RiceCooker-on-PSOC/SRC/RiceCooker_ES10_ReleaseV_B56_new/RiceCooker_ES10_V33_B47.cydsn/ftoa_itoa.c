/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	ftoa_itoa.c		    																			*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

/*******************************************************************************
* Function Name: itoa
********************************************************************************
* Summary:
*    This is a simple function to convert int to ascii code
*
* Parameters:  
*
* Return: 
*
*******************************************************************************/
char *itoa(int num,char *str,int radix)
{ 
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned unum; 
    int i=0,j,k;
    if(radix==10&&num<0) 
    {
        unum=(unsigned)-num;
        str[i++]='-';
    }
    else unum=(unsigned)num; 

    do 
    {
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
    }while(unum);
    str[i]='\0';

    if(str[0]=='-') k=1; 
    else k=0;

    char temp;
    for(j=k;j<=(i-k-1)/2.0;j++)
    {
        temp=str[j];
        str[j]=str[i-j-1];
        str[i-j-1]=temp;
    }
    return str;
}

/*******************************************************************************
* Function Name: ftoa
********************************************************************************
* Summary:
 *    This is a simple implemetation with rigid
 *    parameters:
 *            - Buffer must be 8 chars long
 *            - 3 digits precision max
 *            - absolute range is -524,287 to 524,287 
 *            - resolution (epsilon) is 0.125 and
 *              always rounds down
* Parameters:  
*
* Return: 
*
*******************************************************************************/
 void ftoa(float Value, char* Buffer)
 {
     union
     {
         float f;
         struct
         {
             unsigned int    mantissa_lo : 16;
             unsigned int    mantissa_hi : 7;    
             unsigned int    exponent : 8;
             unsigned int    sign : 1;
         };
     } helper;
     
     unsigned long mantissa;
     signed char exponent;
     unsigned int int_part;
     char frac_part[3];
     int i, count = 0;
     
     helper.f = Value;
     //mantissa is LS 23 bits
     mantissa = helper.mantissa_lo;
     mantissa += ((unsigned long) helper.mantissa_hi << 16);
     //add the 24th bit to get 1.mmmm^eeee format
     mantissa += 0x00800000;
     //exponent is biased by 127
     exponent = (signed char) helper.exponent - 127;
     
     //too big to shove into 8 chars
     if (exponent > 18)
     {
         Buffer[0] = 'I';
         Buffer[1] = 'n';
         Buffer[2] = 'f';
         Buffer[3] = '\0';
         return;
     }
     
     //too small to resolve (resolution of 1/8)
     if (exponent < -3)
     {
         Buffer[0] = '0';
         Buffer[1] = '\0';
         return;
     }
     
     count = 0;
     
     //add negative sign (if applicable)
     if (helper.sign)
     {
         Buffer[0] = '-';
         count++;
     }
     
     //get the integer part
     int_part = mantissa >> (23 - exponent);    
     //convert to string
     itoa(int_part, &Buffer[count],10);
     
     //find the end of the integer
     for (i = 0; i < 8; i++)
         if (Buffer[i] == '\0')
         {
             count = i;
             break;
         }        
 
     //not enough room in the buffer for the frac part    
     if (count > 5)
         return;
     
     //add the decimal point    
     Buffer[count++] = '.';
     
     //use switch to resolve the fractional part
     switch (0x7 & (mantissa  >> (20 - exponent)))
     {
         case 0:
             frac_part[0] = '0';
             frac_part[1] = '0';
             frac_part[2] = '0';
             break;
         case 1:
             frac_part[0] = '1';
             frac_part[1] = '2';
             frac_part[2] = '5';            
             break;
         case 2:
             frac_part[0] = '2';
             frac_part[1] = '5';
             frac_part[2] = '0';            
             break;
         case 3:
             frac_part[0] = '3';
             frac_part[1] = '7';
             frac_part[2] = '5';            
             break;
         case 4:
             frac_part[0] = '5';
             frac_part[1] = '0';
             frac_part[2] = '0';            
             break;
         case 5:
             frac_part[0] = '6';
             frac_part[1] = '2';
             frac_part[2] = '5';            
             break;
         case 6:
             frac_part[0] = '7';
             frac_part[1] = '5';
             frac_part[2] = '0';            
             break;
         case 7:
             frac_part[0] = '8';
             frac_part[1] = '7';
             frac_part[2] = '5';                    
             break;
     }
     
     //add the fractional part to the output string
     for (i = 0; i < 3; i++)
         if (count < 7)
             Buffer[count++] = frac_part[i];
     
     //make sure the output is terminated
     Buffer[count] = '\0';
 }


/*
void hex8_2char(char ch[2], char hex)
{

//  char tmp_char[8];

    int i;
    char tmp_data;

    for(i = 0; i < 2; i ++)
    {
//	    ch = ch + i;
	    tmp_data =  hex & 0x0f;
	    if( tmp_data < 0xa){ch[i]  = tmp_data + 0x30;};
	    if(0x9 <tmp_data){ch[i]  = tmp_data + 0x57;};
	    hex = hex >> 4;
	};
 };

void hex2char_word(char ch[4], uint16 hex)
{
	int i;
	unsigned tmp_data;

	for(i = 0; i < 4; i ++)
	{
		tmp_data =  hex & 0x0f;
		if( tmp_data < 0xa){ch[3-i]  = tmp_data + 0x30;};
		if(0x9 <tmp_data){ch[3-i]  = tmp_data + 0x57;};
		hex = hex >> 4;
	}
}

void hex2char(char ch[8], uint32 hex)
 {

//  char tmp_char[8];

    int i;
    unsigned tmp_data;

    for(i = 0; i < 8; i ++)
    {
//	    ch = ch + i;
	    tmp_data =  hex & 0x0f;
	    if( tmp_data < 0xa){ch[7-i]  = tmp_data + 0x30;};
	    if(0x9 <tmp_data){ch[7-i]  = tmp_data + 0x57;};
	    hex = hex >> 4;
    };
 };

void hex2char_byte(char ch[2], uint8 hex)
{
	int i;
	unsigned tmp_data;

	for(i = 0; i < 2; i ++)
	{
		tmp_data =  hex & 0x0f;
		if( tmp_data < 0xa){ch[1-i]  = tmp_data + 0x30;};
		if(0x9 <tmp_data){ch[1-i]  = tmp_data + 0x57;};
		hex = hex >> 4;
	}
}

unsigned char2hex(char ch, uint32 (*address))
{

    unsigned tmp_dat;
    unsigned j = 0;

    if((ch > 0x2f) & (ch < 0x3a))
    {tmp_dat = ch -0x30; *address = (*address<<4)  + tmp_dat ;};
   
    if((ch > 0x60) & (ch < 0x67))
    {tmp_dat = ch -0x57; *address = (*address<< 4)+ tmp_dat;};

    if((ch > 0x40) & (ch < 0x47))
    {tmp_dat = ch -0x37; *address = (*address<< 4)+ tmp_dat;};
   
    if (!((ch > 0x60) & (ch < 0x67))& !((ch > 0x2f) & (ch < 0x3a))&!((ch > 0x40) & (ch < 0x47)))
    {j = 1;};
    
    return j; 

};
*/
/* [] END OF FILE */
