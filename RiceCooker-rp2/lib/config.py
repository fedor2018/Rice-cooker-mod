from PCD8544 import PCD8544
from ntc import *
import time
from machine import Pin, Timer
"""
"""
VREF=2.5
ntc0=NTC(adc=ADC(Pin(26)), R=2960, Ro=47000, beta=3740, V=VREF, Vref=VREF)
ntc1=NTC(adc=ADC(Pin(27)), R=2960, Ro=47000, beta=3740, V=VREF, Vref=VREF)
ntc2=NTC(adc=ADC(Pin(28)), R=9860, Ro=90500, beta=3950, V=VREF, Vref=VREF)
adc=ADC(Pin(29))

d = PCD8544(spi_id=0, dc=17, din=19, clk=18, dout=16, rst=20)
print(d._spi)
d.begin()
