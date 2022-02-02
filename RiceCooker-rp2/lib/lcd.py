"""
14x6
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

class lcd():
    def __init__(self, pcd=None):
        self.pcd=pcd
        pass
    