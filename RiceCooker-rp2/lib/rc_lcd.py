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
Tall,Tstate - 00:00 00:00
relay - 1/16
"""
import time
from machine import RTC

class rc_lcd():
    def __init__(self, pcd=None):
        self.pcd=pcd
        self.rtc = RTC()
        self.old=time.time()
        
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
#         s=' ' if s[0]==':' else s=':'
        s=' '
        if s.find(':'):
            s=' '
        else:
            s=':'
        self.pcd.LPrint("{:02d}{:1s}{:02d}".format(int(n/60), s, n-int(n/60)))
    
    
                        
