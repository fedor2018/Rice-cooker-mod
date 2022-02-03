from PCD8544 import PCD8544
from ntc import *
import time
from machine import Pin, Timer
import rc_lcd

"""
"""
VT=2.5
adc=ADC(Pin(29))
pan=   NTC(adc=ADC(Pin(26)), R=2960, Ro=47000, beta=3740, adc_t=adc, Vt=VT)
lid=   NTC(adc=ADC(Pin(27)), R=2960, Ro=47000, beta=3740, adc_t=adc, Vt=VT)
heater=NTC(adc=ADC(Pin(28)), R=9860, Ro=90500, beta=3950, adc_t=adc, Vt=VT)

pcd = PCD8544(spi_id=0, dc=1, din=0, clk=2, dout=3, rst=4)
print(pcd._spi)
pcd.begin()
lcd=rc_lcd(pcd)
lcd.ver("Rice cooker", "ver. 1.0", "fedor2018")
