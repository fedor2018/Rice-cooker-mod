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

class rc_lcd():
    def __init__(self, pcd=None):
        self.pcd=pcd
        
    def print_str(self, str, x=0, y=0, fmt='{}'):
        self.pcd.setxy(x,y)
        self.pcd.LPrint(fmt.format(str))
        
    def info(self, *msg):
        """ first info """
        n=1
        for m in *msg:
            self.print_str(m, 0, 1, '{:^}')
            n+=2
        time.sleep(2)
        self.pcd.LClear()
        
        
