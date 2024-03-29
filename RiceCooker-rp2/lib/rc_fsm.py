from time import time
from relay import relay
from buzzer import buzzer

class rc_fsm(relay, buzzer):
    """ rice cooker finity state machine """
    def __init__(self, pin_r=None, pin_b=None):
        self.state="end"
        self.mode=""
        self.LCD=""
        self.fsm=None
        self.pan=0 # current t pan
        self.lid=0 # t lid
        self.T=time() # T
        self.stime=time() # start time
        self.rtime=time()-self.stime # run time
#         self.beep=0
        self.relay="0/0" # 2/16
#         import gc
#         gc.enable()
#         print(gc.mem_alloc())
        import os
        self.fsm_list = [name[:-3] for name in os.listdir('fsm')
                 if name.endswith('.py')]
#         for f in fsm:
#             print(f)
#             self.fsm_list[f]=__import__("fsm."+f) #,globals(),locals(), [], 0)
#         print(self.fsm_list) #['white'].fsm)
#         print(gc.mem_alloc())
#         self.n=0
        self.set_fsm(self.fsm_list[-1])
        self.r=relay(pin_r)
        self.b=buzzer(pin_b)

    def stop(self):
        r.stop()
        
    def set_fsm(self, f):
        """ set current state """
        i=__import__("fsm."+f,None,None,[f]).fsm
        print("set: %s" % i)
        self.fsm=i
        self.mode=self.fsm['mode']
        self.LCD=""
    
    def step(self, pan=0, lid=0):
        """ """
        if self.state not in self.fsm:
            return
        self.rtime=time()-self.stime
#         print("s: {} {}".format(self.state,self.fsm[self.state].keys()))
        for k in self.fsm[self.state].keys():
#             print(k)
            try:
                if type(self.fsm[self.state][k]) is list:
                    lst=self.fsm[self.state][k]
                    if k=='T_gt':
                        for st in lst:
                            if time() > st[0]+self.T:
                                self.next_state(st[1])
                                return
                    elif k=='pan_le':
                        for st in lst:
                            if float(pan) < float(st[0]):
                                self.next_state(st[1])
                                return
                    elif k=='pan_gt':
                        for st in lst:
                            if float(pan) > float(st[0]):
                                self.next_state(st[1])
                                return
                    elif k=='lid_le':
                        for st in lst:
                            if float(lid) < float(st[0]):
                                self.next_state(st[1])
                                return
                    elif k=='lid_gt':
                        for st in lst:
                            if float(lid) > float(st[0]):
                                self.next_state(st[1])
                                return
            except Exception as e:
                print(e)
                print("exp: {} {} {}".format(e, k, self.fsm[self.state].keys()))
                import sys
                sys.print_exception(e)
#         print("s0: {} {}".format(self.state,self.fsm[self.state].keys()))
            
    def next_state(self, next='end'):
        """ """
        self.state=""
        self.relay="0/0"
        self.r.add_state(self.relay)
        print("state=%s" % next)
        if self.fsm is not None:
            if next.find('/')>0:
                self.relay=next
                self.r.add_state(self.relay)
                self.r.run()
            elif next in self.fsm.keys():
                self.state=next
                print("{}=>{}".format(self.state,self.fsm[self.state]))
                if next=='start': self.stime=time()
                if 'LCD' in self.fsm[self.state]:
                    self.LCD=self.fsm[self.state]['LCD']
                if 'T' in self.fsm[self.state]:
                    self.T=time()
                self.b.buzz(self.fsm[self.state].get('beep', ""))
                print("{}: {} {} {}".format(self.state, self.LCD, self.T, self.fsm[next].get('beep', ":")))
            else: #end
#                 self.relay="0/0"
#                 self.r.add_state(self.relay)
                self.LCD=""
                self.stime=0

    def next_fsm(self):
        pass

    def menu(self, k): # pressed keys list
#         if len(k)>0: print(k)
        while k:
            key=k.pop(0)
            print("m: {} {}".format(key, self.is_run()))
            if key=='cancel':
                self.next_state('end')
                k.clear()
            if self.is_run():
                pass
            else:
                if key=='start':
                    self.next_state('start')
                elif key=='select':
                    self.n+=1
                    if self.n >= len(self.fsm_list):
                        self.n=0
                    self.set_fsm(locals()[self.fsm_list[self.n].fsm])
                    pass #import next fsm
                elif key=='up':
                    pass
                elif key=='down':
                    pass
                
 
    def get_time(self):
        """ run, step """
#         print("{}, {}, {}".format(self.rtime, self.stime, self.time))
        if self.stime>0:
            return (time()-self.stime, time()-self.T)
        else:
            return (0,0)
 
    def is_run(self):
        """ cooker in run """
        return False if self.state == 'end' else True
         
