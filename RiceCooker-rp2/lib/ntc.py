from machine import ADC, Pin
from math import log

class NTC():
    """ """
    def __init__(self, adc=None, Vref=3.3, R=10000, Ro=10000.0, To=25.0, beta=3950.0, V=5, Vt=None, adc_t=None ):
        self._adc=adc
        self._vref=Vref
        self._r=R
        self._v=V
        self._r0=Ro
        self._t0=To
        self._beta=beta
        self._Vt=Vt   #example - tl431, 2.5V 
        self._adc_t=adc_t #adc for correct Vref
        
    def vref_cor(self):
        """ vref correct """
        if(self._Vt is not None and self._adc_t is not None):
            self._vref=self._Vt*65535/self._adc_t.read_u16()
        
    def r_UP(self):
        """
        use voltage divider
        Vi--=NTC=--Vo--=R=--GND
        r=(Vi/Vo)*R-R
        """
        try:
            return (self._v/self.in_volt())*self._r-self._r
        except:
            return -1

    def r_DN(self):
        """
        use voltage divider
        Vi--=R=--Vo--=NTC=--GND
                
        """
        try:
            return (self._v/(self._v-self.in_volt()))*self._r-self._r
        except:
            return -1
#        return self._r / (65535/self._adc.read_u16())# - 1)
    
    def in_volt(self):
        self.vref_cor()
        return self._adc.read_u16()*(self._vref/65535)
         
    def to_temp(self, r):
        try:
            steinhart = log(r / self._r0) / self._beta # log(R/Ro) / beta
            steinhart += 1.0 / (self._t0 + 273.15)          # log(R/Ro) / beta + 1/To
            steinhart = (1.0 / steinhart) - 273.15          # Invert, convert to C
            return steinhart
        except:
            return 999
