"""
x14 y6
#:0123567890123
0 special
1 00:00 > 00:00
2 xxx.x   yyy.y 
3 steamX  00:00
4 * 01/16  zzz
5
-------
mode - white|mixed|special|brown|congee
state- pre|cook|steam|warm|error|boilx|
est time - 00:00
pan,lid,heater - XXX YYY ZZZ
Tall,Tstate - 00:00 > 00:00
relay - 1/16
"""
import time
from machine import RTC

class rc_lcd():
    def __init__(self, pcd=None):
        self.pcd=pcd
        self.rtc = RTC()
        self.old=time.time()
        self.s=' '
        
    def print_str(self, str, x=0, y=0, fmt='{}'):
        self.pcd.setxy(x,y)
        self.pcd.LPrint(fmt.format(str))
#         print("{} {} {}".format(x,y,str))
        
    def info(self, *msg):
        """ first info """
        n=0
        for m in msg:
            self.print_str(m, 0, n, '{:^14}')
            n+=1
        time.sleep(2)
#         self.pcd.LClear()

    def temp(self, t):
        self.pcd.setxy(0,2)
        self.pcd.LPrint("{: <#6.1f}{: >#8.1f}".format(t[0],t[1]))
        self.pcd.setxy(8,4)
        self.pcd.LPrint("{: >#6.1f}".format(t[2]))
    
    def alltime(self):
        self.pcd.setxy(8,3)
#         print(self.rtc.datetime())
        n=time.time()-self.old
        self.s=' ' if self.s==':' else ':'
        d=divmod(n, 60)
        self.pcd.LPrint("{:02d}{:1s}{:02d}".format(d[0], self.s, d[1]))

    def conv_time(self, t):
        d=divmod(t, 60)
        return "{:02d}:{:02d}".format(d[0], d[1])
        
        
    def fsm(self, fsm):
        self.print_str(fsm.mode,0,0,"{: <#8s}")
        self.print_str(fsm.state,0,3,"{: <#6s}")
        self.print_str(fsm.LCD,8,0,"{: >#6s}")
        self.print_str(fsm.relay,2,4,"{: ^#5s}")
        t=fsm.get_time()
        self.print_str(self.conv_time(t[0]), 0, 1)
        self.print_str(self.conv_time(t[1]), 8, 1)
                        
    def relay(self, s):
        str="*" if s else " "
        self.print_str(str,0,4)
        
        