"""
"""
from machine import Pin, Timer

class relay():
    """ """
    def __init__(self, pin=None):
        self.pin=pin
        self.pin.value(0)
        self.on=0
        self.off=0
        self.timer_on=Timer(-1)
        self.timer_all=Timer(-1)
        pass
    
    def add_state(self, s):
        n=s.split('/')
        try:
            self.on=int(n[0])
            self.all=int(n[1])
            if(self.on > self.off):
                raise
        except:
            pass
        
    def run(self):
        pass
        
    def cur_state(self):
        return True if self.pin.value()==1 else False

