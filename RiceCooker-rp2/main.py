import config as c
import _thread
import time

def bg_thread():
    while 1:
        c.led.set_color('black')
        time.sleep(1)
        c.led.set_color('red')
        time.sleep(1)


_thread.start_new_thread(bg_thread, ())

#main thread
time.sleep(1)
c.pcd.LClear()
while 1:
    t=c.get_temp()
    print(t)
    c.lcd.temp(t)
    c.lcd.alltime()
    time.sleep(1)
    pass
pass

# time.sleep(1)
# c.led.set_color('green')
# time.sleep(1)
# c.led.set_color('blue')
# time.sleep(1)
# c.led.set_color('cyan',0.2)
# time.sleep(1)
# c.led.set_color('WHITE',0.01)

"""
import fsm_white

print(fsm_white.fsm.keys())
print((fsm_white.fsm['start'].keys()))
print(type(fsm_white.fsm['start']['T_gt']))
"""