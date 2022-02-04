import pcd8544
import ntc
import time
from machine import Pin, Timer
import rc_lcd
import Switch

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
lcd.info("Rice cooker", "ver. 1.0", "fedor2018")

btn={}
btn['select']=Switch(Pin(5, machine.Pin.IN, machine.Pin.PULL_UP))
btn['up']=Switch(Pin(6, machine.Pin.IN, machine.Pin.PULL_UP))
btn['down']=Switch(Pin(7, machine.Pin.IN, machine.Pin.PULL_UP))
btn['start']=Switch(Pin(8, machine.Pin.IN, machine.Pin.PULL_UP))
btn['cancel']=Switch(Pin(9, machine.Pin.IN, machine.Pin.PULL_UP))
btn['unknown']=Switch(Pin(10, machine.Pin.IN, machine.Pin.PULL_UP))

