"""
"""
from machine import Pin, Timer

class relay():
    """ """
    def __init__(self, pin=None):
        self.pin=Pin(pin_num, Pin.OUT) if type(pin) is int else pin
#         self.pin=pin
        self.pin.value(0)
        self.on=0
        self.all=0
        self.timer_on=Timer(-1)
        self.timer_all=Timer(-1)
        self.is_run=False
    
    def add_state(self, s):
        self.stop()
        self.on=0
        self.all=0
        n=s.split('/')
        if(len(n)==2):
            if(int(n[0]) > int(n[1])):
                self.on=int(n[0])
                self.all=int(n[1])
        else:
            print("error: {}".format(s))
            
    def run_on(self):
        if  self.cur_state(): # if on
            self.pin.value(0)
            self.timer_on(-1)
        else:
            self.timer_on(mode=Timer.ONE_SHOT, period=self.on*1000, callback=self.run_on)
            self.pin.value(1)
               
    def run(self):
        self.is_run=True
        self.timer_all(period=self.all*1000, callback=self.run_on)
        self.run_on()
        pass
    
    def stop(self):
        self.timer_on=Timer(-1)
        self.timer_all=Timer(-1)
        self.pin.value(0)
        self.is_run=False
        
    def cur_state(self):
        return True if self.pin.value()==1 else False

#     def step(self):
#         if self.on==0:
#             self.pin.value(0)
#         if self.on>0 and self.all>self.on:
#             if 
#         pass
    
    