#  PCD8544.py

from machine import Pin, SPI, SoftSPI
from array import array
import utime, time
from ustruct import pack

class PCD8544():
    def __init__(self, spi_id=None, rst=None, ce=None, dc=None, din=None, clk=None, dout=None):
        self._rst = Pin(rst, Pin.OUT) if rst else None # 14
        self._ce = Pin(ce, Pin.OUT) if ce else ce   # 13
        if self._ce: self.ce(1)
        self._dc = Pin(dc, Pin.OUT) if dc else dc   # 12
        self._dc.high()
        
        self._row = 0
        self._col = 0
        self._x = 0
        self._y = 0
        #127 character ascii font, 5x8 size characters
        self.font = bytearray(b'\x00\x00\x00\x00\x00\x00\x00\x5f\x00\x00\x00\x07\x00\x07\x00\x14\x7f\x14\x7f\x14\x24\x2a\x7f\x2a\x12\x23\x13\x08\x64\x62\x36\x49\x55\x22\x50\x00\x05\x03\x00\x00\x00\x1c\x22\x41\x00\x00\x41\x22\x1c\x00\x14\x08\x3e\x08\x14\x08\x08\x3e\x08\x08\x00\x50\x30\x00\x00\x08\x08\x08\x08\x08\x00\x60\x60\x00\x00\x20\x10\x08\x04\x02\x3e\x51\x49\x45\x3e\x00\x42\x7f\x40\x00\x42\x61\x51\x49\x46\x21\x41\x45\x4b\x31\x18\x14\x12\x7f\x10\x27\x45\x45\x45\x39\x3c\x4a\x49\x49\x30\x01\x71\x09\x05\x03\x36\x49\x49\x49\x36\x06\x49\x49\x29\x1e\x00\x36\x36\x00\x00\x00\x56\x36\x00\x00\x08\x14\x22\x41\x00\x14\x14\x14\x14\x14\x00\x41\x22\x14\x08\x02\x01\x51\x09\x06\x32\x49\x79\x41\x3e\x7e\x11\x11\x11\x7e\x7f\x49\x49\x49\x36\x3e\x41\x41\x41\x22\x7f\x41\x41\x22\x1c\x7f\x49\x49\x49\x41\x7f\x09\x09\x09\x01\x3e\x41\x49\x49\x7a\x7f\x08\x08\x08\x7f\x00\x41\x7f\x41\x00\x20\x40\x41\x3f\x01\x7f\x08\x14\x22\x41\x7f\x40\x40\x40\x40\x7f\x02\x0c\x02\x7f\x7f\x04\x08\x10\x7f\x3e\x41\x41\x41\x3e\x7f\x09\x09\x09\x06\x3e\x41\x51\x21\x5e\x7f\x09\x19\x29\x46\x46\x49\x49\x49\x31\x01\x01\x7f\x01\x01\x3f\x40\x40\x40\x3f\x1f\x20\x40\x20\x1f\x3f\x40\x38\x40\x3f\x63\x14\x08\x14\x63\x07\x08\x70\x08\x07\x61\x51\x49\x45\x43\x00\x7f\x41\x41\x00\x02\x04\x08\x10\x20\x00\x41\x41\x7f\x00\x04\x02\x01\x02\x04\x40\x40\x40\x40\x40\x00\x01\x02\x04\x00\x20\x54\x54\x54\x78\x7f\x48\x44\x44\x38\x38\x44\x44\x44\x20\x38\x44\x44\x48\x7f\x38\x54\x54\x54\x18\x08\x7e\x09\x01\x02\x0c\x52\x52\x52\x3e\x7f\x08\x04\x04\x78\x00\x44\x7d\x40\x00\x20\x40\x44\x3d\x00\x7f\x10\x28\x44\x00\x00\x41\x7f\x40\x00\x7c\x04\x18\x04\x78\x7c\x08\x04\x04\x78\x38\x44\x44\x44\x38\x7c\x14\x14\x14\x08\x08\x14\x14\x18\x7c\x7c\x08\x04\x04\x08\x48\x54\x54\x54\x20\x04\x3f\x44\x40\x20\x3c\x40\x40\x20\x7c\x1c\x20\x40\x20\x1c\x3c\x40\x30\x40\x3c\x44\x28\x10\x28\x44\x0c\x50\x50\x50\x3c\x44\x64\x54\x4c\x44\x00\x08\x36\x41\x00\x00\x00\x7f\x00\x00\x00\x41\x36\x08\x00\x10\x08\x08\x10\x08\x00\x00\x00\x00\x00')
#         self.LInit = bytearray(b'\x21\xbc\x04\x14\x20\x0C') #contast, TCx, BSx,Normal  

        if spi_id is not None:
            self._spi = SPI(spi_id, baudrate=2000000, polarity=0, phase=0,
                            sck=Pin(clk), mosi=Pin(din), miso=Pin(dout))
        else:
            self._spi = SoftSPI(baudrate=500000, polarity=0, phase=0,
                            sck=Pin(clk), mosi=Pin(din), miso=Pin(dout))

    def ce(self, l=0):
        if self._ce:
            self._ce.value(l)

    def command(self,c, ext=0):
        b = bytearray(2)
        b[0] = 0x20
        if ext:
            b[0] += 1
        b[1] = c
        self._dc.low()
        self.ce(0)
#         print(['{:x}'.format(item) for item in b])
#             "CMD: %x%x" % b[0], b[1])
        self._spi.write(b)
        self.ce(1)

    def data(self, data):
#         t0=utime.ticks_add(utime.ticks_us(),100)
        self._dc.high()
        self.ce(0)
        self._spi.write(data)
#         print("DATA: {}".format(data))
        self.ce(1)
#         print("delay: %dus" % (utime.ticks_diff(utime.ticks_us(),t0)))
        
    def reset(self):
        if self._rst:
            self._rst.low()
            time.sleep_ms(50)        # sleep for 50 milliseconds
            self._rst.high()

    # begin
    def begin(self):
        self.reset()
        self.command(0xc) #normal
        self.command(0x13, 1) #bias
        self.command(0x4, 1) #temp
        self.command(128+70, 1) #contrast
#         self.command()
        
        self.clear()
        self.display()

    # display
    def display(self):
        self.command(0x40) #y=0
        self.command(0x80) #x=0
        self.data(self._buf)
        
    def p_char(self, ch):
        fp = (ord(ch)-0x20) * 5
        char_buf = array('b',[0,0,0,0,0])
        f = open('font5x7.fnt','rb')
        f.seek(fp)
        char_buf = f.read(5)
        bp = 84*self._row + 6*self._col
        for x in range (0,5):
            self._buf[bp+x] = char_buf[x]
            self._buf[bp+5] = 0 # put in inter char space
        self._col += 1
        if (self._col>13):
            self._col = 0
            self._row += 1
            if (self._row>5):
                self._row = 0

    def p_string(self, str):
        for ch in (str):
            self.p_char(ch)

    def clear(self):
        self._buf=bytearray(84 * int(48 / 8))
        self._row = 0
        self._col = 0
                
    def pixel(self,x,y,fill):
        r = int(y/8)
        i = r * 84 + x
        b = y % 8
        self._buf[i] = self._buf[i] | ( 1 << b )
        
    def LPrint (self, message):
        text = bytearray()
        for letter in message:
            i = (ord(letter) - 32) * 5
            for b in range (0,5):
                text.append(self.font[i+b])
            text.append(0x00)
        self.data(text)

    def LSetY(self, y):
        self.command(0x40+y)

    def LSetX(self, x):
        self.command(0x80+x)

    def setxy(self,x=-1,y=-1):
        if x>=0:
            self.LSetX(x*6)
        if y>=0:
            self.LSetY(y)
        
    def LClear(self):
        data = bytearray(504)
        self.data(data)
        return

    def init(self):
        self.data(self.LInit)
