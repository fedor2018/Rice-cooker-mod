"""
"""
from machine import Pin, Timer
from time import time

class relay():
    """ """
    def __init__(self, pin=None):
        self.pin=Pin(pin, Pin.OUT) if type(pin) is int else pin
#         self.pin=pin
        self.pin.value(0)
        self.on=0
        self.off=0
        self.tim=Timer()
#         self.timer_on=Timer()
#         self.timer_all=Timer()
        self.is_run=False
        self.t=0
        self.t0=0

    def add_state(self, s):
#         self.stop()
        self.on=0
        self.off=0
        n=s.split('/')
#         print(n)
        if(len(n)==2):
            if(int(n[0]) <= int(n[1]) and int(n[0])>0 and int(n[1])>0):
                self.on=int(n[0])*1000
                self.off=int(n[1])*1000-self.on
            print("{} {}".format(self.on, self.off))
        else:
            print("error: {}".format(s))

    def run_off(self, t=''):
        self.pin.value(0)
        print('\\', end='')
        self.tim.init(mode=Timer.ONE_SHOT, period=self.off, callback=self.run_on)
        
    def run_on(self, t=''):
#         print("run on {} {} {}".format(self.len, self.cnt,self.tim))
        self.tim.init(mode=Timer.ONE_SHOT, period=self.on, callback=self.run_off)
        self.pin.value(1)
        print('/', end='')

    def run(self):
        if self.on > 0 and self.off>=0:
            self.is_run=True
            if self.off==0:
                self.pin.value(1)
            else:
                self.run_on()

    def stop(self):
        self.tim.deinit()
        self.pin.value(0)
        self.is_run=False

    def cur_state(self):
#         print("{}".format(self.pin.value()),end='')
        return True if self.pin.value()==1 else False

    