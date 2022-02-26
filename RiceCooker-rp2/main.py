import config as c
import _thread
import gc
import time

t=(0, 0, 0, 0)
stop=0
def bg_thread():
    global t, stop
    while 1:
        try:
            t=c.get_temp()
    #         print(t)
            c.led.set_color('black')
            time.sleep_ms(500)
            c.led.set_color('red')
            time.sleep_ms(500)
            if stop: _thread.exit()
        except Exception as e:
            print(e)
            import sys
            sys.print_exception(e)
            stop=1

_thread.start_new_thread(bg_thread, ())
#main thread
time.sleep(1)
c.pcd.LClear()
while stop==0:
#     print(t)
    try:
#         print(int(gc.mem_free()), end="")
#         print(" ", end="")
#         print(int(gc.mem_alloc()))
        gc.collect()
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
    except Exception as e:
        print(e)
        import sys
        sys.print_exception(e)
        stop=1

"""
import fsm_white

print(fsm_white.fsm.keys())
print((fsm_white.fsm['start'].keys()))
print(type(fsm_white.fsm['start']['T_gt']))
"""