"""
"""
from machine import Pin, Timer

class relay():
    """ """
    def __init__(self, pin=None):
        self.pin=Pin(pin, Pin.OUT) if type(pin) is int else pin
#         self.pin=pin
        self.pin.value(0)
        self.on=0
        self.all=0
        self.timer_on=Timer()
        self.timer_all=Timer()
        self.is_run=False
    
    def add_state(self, s):
#         self.stop()
        self.on=0
        self.all=0
        n=s.split('/')
#         print(n)
        if(len(n)==2):
            if(int(n[0]) <= int(n[1]) and int(n[0])>0 and int(n[1])>0):
                self.on=int(n[0])
                self.all=int(n[1])
#             print("{} {}".format(self.on, self.all))
        else:
            print("error: {}".format(s))
            
    def run_on(self, t):
        if  self.cur_state(): # if on
#             print("set 0")
            self.pin.value(0)
            self.timer_on.deinit()
        if self.on>0:
#             print("run on {} {} {}".format(self.on, self.all,self.timer_on))
            self.timer_on.init(mode=Timer.ONE_SHOT, period=self.on*1000, callback=self.run_on)
    #             print("{}".format(self.timer_on))
            self.pin.value(1)
               
    def run(self):
#         print("run {} {} {}".format(self.on, self.all,self.timer_on))
        if self.on > 0 and self.all>0:
            self.is_run=True
            if self.on==self.all:
                self.pin.value(1)
            else:
                self.timer_all.init(period=self.all*1000, mode=Timer.PERIODIC, callback=self.run_on)
        #         print("{}".format(self.timer_all))
                self.run_on('')
    #         print("run 1")
        pass
    
    def stop(self):
#         print("stop0")
        self.timer_on.deinit()
        self.timer_all.deinit()
        self.pin.value(0)
        self.is_run=False
#         print("stop")
        
    def cur_state(self):
        return True if self.pin.value()==1 else False

#     def step(self):
#         if self.on==0:
#             self.pin.value(0)
#         if self.on>0 and self.all>self.on:
#             if 
#         pass
    
    