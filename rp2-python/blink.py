from machine import Pin, Timer
led = Pin(25, Pin.OUT)
led2 = Pin(14, Pin.OUT)
led.value(0)
led2.value(1)
tim = Timer()
def tick(timer):
 global led, led2
 led.toggle()
 led2.toggle()
 
tim.init(freq=1, mode=Timer.PERIODIC, callback=tick)
