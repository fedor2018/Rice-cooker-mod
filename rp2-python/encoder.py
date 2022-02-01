from  rotary_irq_rp2 import RotaryIRQ
import utime
from machine import Pin, Timer

def pkey(line):
    print("line=",line);

enc_menu = RotaryIRQ(11, 12,
                     pull_up=True,
                     half_step=False,
                     min_val=0, 
                     max_val=24, 
                     reverse=True,
                     range_mode=RotaryIRQ.RANGE_WRAP)
enc_menu.add_listener(lambda: print(enc_menu.value()))

IRQ_RISING_FALLING = Pin.IRQ_RISING | Pin.IRQ_FALLING
def mkey(l):
    print(l)
    print(key_menu.value())

timer = Timer()
def debounce(pin):
    # Start or replace a timer for 200ms, and trigger on_pressed.
    timer.init(mode=Timer.ONE_SHOT, period=50, callback=mkey)

key_menu=Pin(13, Pin.IN, Pin.PULL_UP)
key_menu.irq(debounce, IRQ_RISING_FALLING)

while 1:
    pass

