import config as c
import _thread
import time
t=(0, 0, 0, 0)
stop=0
def bg_thread():
    global t, stop
    while 1:
        t=c.get_temp()
        print(t)
        c.led.set_color('black')
        time.sleep_ms(500)
        c.led.set_color('red')
        time.sleep_ms(500)
        if stop: _thread.exit()

_thread.start_new_thread(bg_thread, ())
#main thread
# try:
time.sleep(1)
c.pcd.LClear()
while 1:
#     print(t)
    try:
        c.lcd.temp(t)
        c.lcd.alltime()
        c.rc.menu(c.b.keys)
        c.rc.step(t[0], t[1])
        c.lcd.fsm(c.rc)
        c.lcd.relay(c.rc.r.cur_state())
        time.sleep_ms(500)
    except KeyboardInterrupt:
        print("stop")
        stop=1


"""
import fsm_white

print(fsm_white.fsm.keys())
print((fsm_white.fsm['start'].keys()))
print(type(fsm_white.fsm['start']['T_gt']))
"""