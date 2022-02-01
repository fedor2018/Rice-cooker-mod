from machine import ADC, Pin
from ntc import *


adc0 = ADC(Pin(26))     # create ADC object on ADC pin
adc1 = ADC(Pin(27))     # create ADC object on ADC pin
#adc=None, Vref=3.3, R=10000, Ro=10000.0, To=25.0, beta=3950.0, V=5 )
ntc0=NTC(adc=ADC(Pin(26)), R=3300, Ro=47000, beta=3740)
ntc1=NTC(adc=ADC(Pin(27)), R=3300, Ro=47000, beta=3740)

print ("{} V".format(ntc0.in_volt()))
print ("{} V".format(ntc1.in_volt()))

print("{} ohm".format(ntc0.r_UP()))
print("{} ohm".format(ntc1.r_UP()))

print("{} C".format(ntc0.to_temp(ntc0.r_UP())))
print("{} C".format(ntc1.to_temp(ntc1.r_UP())))



