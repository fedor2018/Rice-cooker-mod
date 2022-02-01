Sensors&vars:
T - time stage
pan - pan sensor
lid  - lid sensor
-----------------
pan> panUP
pan< panDN
-----------------
start, T=1'36", LCD=PRE
  pan>125 => warm
  T<0 => pre0
  pan>60 => boil
pre0, T=14'24", LCD=PRE
  T<0 => stand
  pan<50 => r=8/16
  pan>125 => warm
  pan>50 => pre1
pre1, LCD=PRE
  T<0 =>stand
  pan<50 => r3/16
  pan>125 => warm
  pan>50 => r0/0
stand, T=25'36"
  pan>134 => warm
  pan<82.9 => r16/16
  pan>82.9 => weight
  T<0 => boil1
weight, T=25'36"
  pan>134 => warm
  lid<71.5 => r16/16
  lid>71.5 => boil0
  T<0 => boil1
boil0, T=19'12"
  pan<120 => r=16/16
  pan>120 => boil1
  T<0 => boil1
boil1, 
  pan<120 => r=10/16
  pan>120 => r=7/16
  pan>134 => steam0
  T<0 => ?
steam0, T=3'12"
  T<0 steam1
  T>0 => r=0/0
steam1, T=3'12"
  T>0 => r=1/16
  T<0 => steam2
steam2, T=6'24"
  T>0 => r=0/0
  T<0 => warm
warm, T=12hours
  pan>71.5 => r=0/0
  pan<71.5 => r=1/16
  T<0 => end


 