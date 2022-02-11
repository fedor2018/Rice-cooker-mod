from machine import Pin, Timer

class buzzer():
    """
    buzz("500:3) - 3*(500+500)ms
    """
    def __init__(self, pin=None):
        self.pin=Pin(pin_num, Pin.OUT) if type(pin) is int else pin
        self.len=0 # beep/pause delay
        self.cnt=0 # beep counter
        self.timer=Timer(-1)
        
    def buzz(self, s):
        n=s.split(':')
        if(len(n)==2):
            self.len=int(n[0])
            self.cnt=int(n[1])
            self.beep()
        
    def beep(self):
        self.pin.value(1)
        self.timer(mode=Timer.ONE_SHOT, period=self.len, callback=pause)

    def pause(self):
        self.pin.value(0)
        self.cnt-=1
        if self.cnt<=0:
            self.timer(-1)
        else:
            self.timer(mode=Timer.ONE_SHOT, period=self.len, callback=beep)

