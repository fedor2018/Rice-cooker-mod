import time
from PCD8544 import PCD8544
import lcd_gfx
# import network
import bmp

print("start")

d = PCD8544(spi_id=0, dc=17, din=19, clk=18, dout=16)
print(d._spi)

d.begin()

d.p_string('The quick brown fox jumped over the lazy dog')
d.display()
time.sleep(1)

d.clear()
lcd_gfx.drawTrie(42,2,21,23,63,23,d,1)
d.display()
time.sleep(1)

lcd_gfx.drawFillRect(10,12,20,20,d,1)
d.display()
time.sleep(1)

lcd_gfx.drawCircle(70,24,10,d,1)
d.display()
time.sleep(1)

d.clear()
bmp.bmp('icon.bmp',d)
d.display()
time.sleep(1)

# d.init()
d.LClear()
d.setxy(0,0)
d.LPrint("aa")
for y in range(0,6):
    d.setxy(y, y)
    d.LPrint("Hello %d" % y)
    print(y)
    time.sleep(1)
# d.LSetY(2)
# d.LSetX(25)
# d.LPrint("More Text!")



