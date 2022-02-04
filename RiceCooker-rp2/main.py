import lib.config as c
import _thread

def bg_thread():
    pass

_thread.start_new_thread(bg_thread, ())

#main thread
pass

"""
import fsm_white

print(fsm_white.fsm.keys())
print((fsm_white.fsm['start'].keys()))
print(type(fsm_white.fsm['start']['T_gt']))
"""