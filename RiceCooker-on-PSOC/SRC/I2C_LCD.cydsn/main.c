#include <device.h>

int main(void)
{
    CyGlobalIntEnable;
    I2C_Start();
    I2C_LCD_Start();
    I2C_LCD_SetContrast(50);
    CyDelay(1000u);   
    I2C_LCD_Position(0u, 19u);
    I2C_LCD_PrintString("s");
    I2C_LCD_Position(0u, 0u);
    I2C_LCD_PrintString("a");
    I2C_LCD_WriteControl(I2C_LCD_CURSOR_WINK);
    
    
    I2C_LCD_Position(1u, 0u);
    I2C_LCD_PrintString("Cypress PSOC 4");
    I2C_LCD_Position(2u, 2u);
    I2C_LCD_PrintString("CYPRESS Demo");
    I2C_LCD_WriteControl(I2C_LCD_CURSOR_WINK);    
    I2C_LCD_Position(3u, 10u);
    I2C_LCD_PutChar('$');    
    
}