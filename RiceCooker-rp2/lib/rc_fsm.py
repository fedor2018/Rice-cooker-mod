from time import time

class rc_fsm():
    """ rice cooker finity state machine """
    def __init__(self, fsm=None):
        self.state=""
        self.mode=""
        self.LCD=""
        self.pan=0 # current t pan
        self.lid=0 # t lid
        self.time=0 # T
        self.stime=0 # start time
        self.rtime=0 # run time
        self.beep=0
        self.relay="0/0" # 2/16
        self.set_fsm(fsm)
    
    def set_fsm(self, fsm):
        """ set current state """
        self.fsm=fsm
        if self.fsm is not None:
            self.mode=self.fsm['mode']
        self.LCD=""
    
    def step(self, pan=0, lid=0):
        """ """
        if self.state=="":
            return
        self.rtime=time()-self.stime
        t=time()-self.time
        for k in self.fsm[self.state].keys():
            if type(self.fsm[self.state][k] is list):
                lst=self.fsm[self.state][k]
                if k=='T_gt':
                    for st in lst:
                        if t > st[0]:
                            self.next_state(st[1])
                elif k=='pan_le':
                    for st in lst:
                        if float(pan) < float(st[0]):
                            self.next_state(st[1])
                elif k=='pan_gt':
                    for st in lst:
                        if float(pan) > float(st[0]):
                            self.next_state(st[1])
                elif k=='lid_le':
                    for st in lst:
                        if float(lid) < float(st[0]):
                            self.next_state(st[1])
                elif k=='lid_gt':
                    for st in lst:
                        if float(lid) > float(st[0]):
                            self.next_state(st[1])
            
    def next_state(self, next='end'):
        """ """
        self.state=""
        self.LCD=""
        if self.fsm is not None:
            if next.find('/')>0:
                self.relay=next
            elif next in self.fsm.keys():
                print("{}=>{}".format(next,self.fsm[next]))
                self.state=next
                if next=='start': self.stime=time()
                self.LCD=self.fsm[next]['LCD']
                self.time=self.fsm[next].get('T', self.time)
                self.beep=self.fsm[next].get('beep', 0)
                print("{}: {} {} {}".format(self.state, self.LCD, self.time, self.beep))
            else: #end
                self.relay="0/0"
                self.stime=0

    def menu(self, k): # pressed keys list
#         print(k)
        while k:
            key=k.pop(0)
#             print("m: {}".format(key))
            if key=='start':
                self.next_state('start')
            elif key=='cancel':
                self.next_state('end')
#         k.clear()

    def get_time(self):
        """ run, step """
#         print("{}, {}, {}".format(self.rtime, self.stime, self.time))
        if self.stime>0:
            return (self.rtime, time()-self.time)
        else:
            return (0,0)
            