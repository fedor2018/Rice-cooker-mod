"""
"""
class relay():
    """ """
    def __init__(self, pin=None):
        self.pin=pin
        self.on=0
        self.off=0
        self.timer_on=machine.Timer(-1)
        self.timer_all=machine.Timer(-1)
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
        
        
    def cur_state(self):
        return True if self.pin.value() else False

