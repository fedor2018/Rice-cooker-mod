from machine import Pin, Timer
# import machine

class buzzer():
    """
    buzz("500:3) - 3*(500+500)ms
    """
    def __init__(self, pin=None):
        self.pin=Pin(pin, Pin.OUT) if type(pin) is int else pin
        self.len=0 # beep/pause delay
        self.cnt=0 # beep counter
        self.tim=Timer()
        
    def buzz(self, s):
        n=s.split(':')
        if(len(n)==2):
            self.len=int(n[0])
            self.cnt=int(n[1])
            self.run_on()

    def run_off(self, t=''):
#         print('b', end='')
        self.pin.value(0)
        self.cnt-=1
        if self.cnt<=0:
            self.tim.deinit()
        else:
            self.tim.init(mode=Timer.ONE_SHOT, period=self.len, callback=self.run_on)
        
    def run_on(self, t=''):
#         print("run on {} {} {}".format(self.len, self.cnt,self.tim))
        self.tim.init(mode=Timer.ONE_SHOT, period=self.len, callback=self.run_off)
        self.pin.value(1)

    def a(self, t):
        pass

