from pcd8544 import *
from ntc import NTC
import time
from machine import Pin, Timer, ADC
from rc_lcd import *
from Switch import *
from ws2812b import ws2812b
from led_zero import led_zero

"""
"""
VT=2.5
R1=3250
R2=9950
adc=ADC(Pin(29))
pan=   NTC(adc=ADC(Pin(26)), R=R1, Ro=47000, beta=3740, adc_t=adc, Vt=VT)
lid=   NTC(adc=ADC(Pin(27)), R=R1, Ro=47000, beta=3740, adc_t=adc, Vt=VT)
heater=NTC(adc=ADC(Pin(28)), R=R2, Ro=90500, beta=3950, adc_t=adc, Vt=VT)

pcd = PCD8544(spi_id=0, dc=1, din=3, clk=2, dout=0, rst=4)
# print(pcd._spi)
pcd.begin()
lcd=rc_lcd(pcd)
lcd.info("Rice cooker", "ver. 1.0", "fedor2018","","01234567890123")

btn={}
btn['select']=Switch(Pin(5, Pin.IN, Pin.PULL_UP))
btn['up']=Switch(Pin(6, Pin.IN, Pin.PULL_UP))
btn['down']=Switch(Pin(7, Pin.IN, Pin.PULL_UP))
btn['start']=Switch(Pin(8, Pin.IN, Pin.PULL_UP))
btn['cancel']=Switch(Pin(9, Pin.IN, Pin.PULL_UP))
btn['unknown']=Switch(Pin(10, Pin.IN, Pin.PULL_UP))

led=led_zero()

def get_temp():
    return (pan.r_UP(), lid.r_UP(), heater.r_UP(), pan._vref)

    