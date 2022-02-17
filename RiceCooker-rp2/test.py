from buzzer import buzzer
from machine import Pin, Timer
import time
import micropython
micropython.alloc_emergency_exception_buf(100)
from relay import relay
from led_zero import led_zero

#
led=led_zero(0)
r=relay(14)
b=buzzer(11)
# b.buzz("100:1")
# tim = Timer(period=5000, mode=Timer.ONE_SHOT, callback=lambda t:print(1))
# tim.init(period=2000, mode=Timer.PERIODIC, callback=lambda t:print(2))
print("run")
led.set_color('green')
r.add_state("4/8")
r.run()
# while 1:
#     if r.cur_state():
#         led.set_color('red')
#     else:
#         led.set_color('black')
#     time.sleep_ms(200)
 
