from PCD8544 import PCD8544
import lcd_gfx
from ntc import *
import time
from machine import Pin, Timer

led = Pin(25, Pin.OUT, value=1)
# """
r=Pin(10, Pin.OUT, value=0)
IRQ_RISING_FALLING = Pin.IRQ_RISING | Pin.IRQ_FALLING
def mkey(l):
    r.value( 0 if key_menu.value() else 1)
#     print(l)
    print("pin=%d key=%d" % (r.value(), (key_menu.value())))
#     print(key_menu.value())

timer = Timer()
def debounce(pin):
    timer.init(mode=Timer.ONE_SHOT, period=50, callback=mkey)

key_menu=Pin(13, Pin.IN, Pin.PULL_UP)
key_menu.irq(debounce, IRQ_RISING_FALLING)
# """
VREF=2.5
ntc0=NTC(adc=ADC(Pin(26)), R=2960, Ro=47000, beta=3740, V=VREF, Vref=VREF)
ntc1=NTC(adc=ADC(Pin(27)), R=2960, Ro=47000, beta=3740, V=VREF, Vref=VREF)
ntc2=NTC(adc=ADC(Pin(28)), R=9860, Ro=90500, beta=3950, V=VREF, Vref=VREF)
adc=ADC(Pin(29))

d = PCD8544(spi_id=0, dc=17, din=19, clk=18, dout=16, rst=20)
print(d._spi)
d.begin()
# 
# d.p_string("Start ")
# d.display()
# time.sleep(1)
# d.init()
# d.LClear()
dot=""
while 1:
    d.LClear()
    d.setxy(0,0)
    d.LPrint ("{:.3f}V".format(ntc0.in_volt()))
    d.setxy(7,0)
    d.LPrint ("{:.3f}V ".format(ntc1.in_volt()))

    r0=ntc0.r_DN()
    d.setxy(0,1)
    d.LPrint("{:.2f}K".format(r0/1000)) 
    r1=ntc1.r_DN()
    d.setxy(7,1)
    d.LPrint("{:.2f}K".format(r1/1000))

    d.setxy(0,2)
    d.LPrint("{:.1f}C".format(ntc0.to_temp(ntc0.r_DN())))
    d.setxy(7,2)
    d.LPrint("{:.1f}C".format(ntc1.to_temp(ntc1.r_DN())))

    d.setxy(0,4)
    d.LPrint("{:3.1f}C".format(ntc2.to_temp(ntc2.r_DN())))
    r2=ntc2.r_DN()
    d.LPrint(" {:.2f}K".format(r2/1000))

    d.setxy(0,5)
    if len(dot)>=14:
        dot=""
    dot += "."
    d.LPrint(dot)
#    d.display()
    d.setxy(3,3)
    d.LPrint("*" if r.value() else ". ")
#     d.LPrint(" {}".format(adc.read_u16()))
    led.value( 0 if led.value() else 1)
#     print("%d %d" % (r.value(), key_menu.value()))
    time.sleep(1)
