from DebouncerPIO import DebouncerLowPIO

class btn_pio(DebouncerLowPIO):
    """ array buttons """
    def __init__(self, sm=0, btn_list=None, handler=None): #pin: "name",...
        self.handler=handler if handler is not None else self.press
        self.keys=[]
        self.btn={}
        self.sm=sm
        for n in btn_list.keys():
            if self.sm>7: raise("too many StateMachines")
            self.btn[self.sm]=btn_list[n]
            DebouncerLowPIO(self.sm, n, self.handler)
            self.sm+=1
    
    def press(self, sm): #StateMachine(N)
        n=int(str(sm)[13])
        self.keys.append(self.btn[n])
#         print("{}:{}".format(n,self.btn[n]))
