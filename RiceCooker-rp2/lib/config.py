from pcd8544 import *
from ntc import NTC
import time
from machine import Pin, Timer, ADC
from rc_lcd import *
from led_zero import led_zero
from relay import relay
from btn_pio import btn_pio
from rc_fsm import rc_fsm
# from fsm_white import fsm

"""
"""
VT=2.5
R1=3250
R2=9950
adc=ADC(Pin(29))
pan=   NTC(adc=ADC(Pin(26)), R=R1, Ro=47000, beta=3740, adc_t=adc, Vt=VT)
lid=   NTC(adc=ADC(Pin(27)), R=R1, Ro=47000, beta=3740, adc_t=adc, Vt=VT)
heater=NTC(adc=ADC(Pin(28)), R=R2, Ro=90500, beta=3950, adc_t=adc, Vt=VT)

pcd = PCD8544(spi_id=0, dc=1, din=3, clk=2, dout=0, rst=4, pwm=15)
# print(pcd._spi)
pcd.begin()
pcd.pwm(80,100)
lcd=rc_lcd(pcd)
lcd.info("Rice  cooker", "ver. 1.0", "fedor2018","","01234567890123")

led=led_zero(0)
b=btn_pio(1, {5:'select', 6:'up', 7:'down', 8:'cancel', 9:'none', 10:'start'})

rc=rc_fsm(('fsm_white'), 14, 11)
rc.b.buzz("200:2")

def get_temp():
    return (pan.r_UP(), lid.r_UP(), heater.r_UP(), pan._vref)

