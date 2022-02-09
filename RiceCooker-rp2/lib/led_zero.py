import rp2
from machine import Pin

@rp2.asm_pio(sideset_init=rp2.PIO.OUT_LOW, out_shiftdir=rp2.PIO.SHIFT_LEFT, autopull=True, pull_thresh=24)
def ws2812():
    T1 = 2
    T2 = 5
    T3 = 3
    wrap_target()
    label("bitloop")
    out(x, 1)               .side(0)    [T3 - 1]
    jmp(not_x, "do_zero")   .side(1)    [T1 - 1]
    jmp("bitloop")          .side(1)    [T2 - 1]
    label("do_zero")
    nop()                   .side(0)    [T2 - 1]
    wrap()

class led_zero():
    """ """
    def __init__(self, sm=0):
        self.sm = rp2.StateMachine(sm, ws2812, freq=8000000, sideset_base=Pin(16))
        self.sm.active(1)
        self.brightness = 0.1
        self.COLORS={
            'BLACK': (0, 0, 0),
            'RED':   (255, 0, 0),
            'YELLOW': (255, 150, 0),
            'GREEN': (0, 255, 0),
            'CYAN': (0, 0x8b, 0x8b),
            'BLUE': (0, 0, 255),
            'PURPLE': (180, 0, 255),
            'WHITE': (255, 255, 255),
        }
        
    def set_color(self, c='BLACK', b=None):
        """ """
        if b is not None:
            self.brightness=b
        ar=0
        color=self.COLORS[c.upper()]

        ar+=int(color[2] * self.brightness)<<(0) #blue
        ar+=int(color[1] * self.brightness)<<(16)#green
        ar+=int(color[0] * self.brightness)<<(8) #red
#         for i in range(3):
#             ar+=int(color[2-i] * self.brightness)<<(8*i)
#             print("{:d}:{:x}:{:x}:{:x}".format(i,ar,color[2-i],int(color[2-i] * self.brightness)))
#         print("{:06x}".format(ar))
        self.sm.put(ar, 8)
#         time.sleep_ms(10)

