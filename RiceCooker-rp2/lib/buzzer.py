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
        self.tim=Timer(-1)
        
    def buzz(self, s):
        n=s.split(':')
        if(len(n)==2):
            self.len=int(n[0])
            self.cnt=int(n[1])
            self.run_on()

    def run_off(self):
        self.pin.value(0)
        self.cnt-=1
        if self.cnt<=0:
            self.tim(-1)
        else:
            self.tim(mode=Timer.ONE_SHOT, period=self.len, callback=self.run_on)
        
    def run_on(self):
        self.pin.value(1)
        self.tim(mode=Timer.ONE_SHOT, period=self.len, callback=self.run_off)

    def a(self, t):
        pass

