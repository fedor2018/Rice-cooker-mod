
fsm={
    "mode": "white"
    "start": {
        'LCD': 'PRE',
        'T': 0, #??
        'pan_gt': [125,'warm'], #1'36"
        'pan_gt': [60, 'boil'],
        'T_gt': [96, 'pre0'] 
        },
    "pre0": {
        'T':0,
        'T_gt': [864, 'stand'], #14'24"
        'pan_le': [50, '8/16'],
        'pan_gt': [50, '0/0'],
        'pan_gt': [125, 'warm']
        },
    "pre1": {
        'T_gt': [864, 'stand'],
        'pan_le': [50, '3/16'],
        'pan_gt': [50, '0/0'],
        'pan_gt': [125, 'warm']
        },
    "stand": {
        'LCD':'BOILING',
        'T':0,
        'T_gt': [1536, 'boil1'], #25'36"
        'pan_le': [82.9, '16/16'],
        'pan_gt': [82.9, 'weight'],
        'pan_gt': [134, 'warm']
        },
    "weight": {
        'T':0,
        'T_gt': [1536, 'boil1'],
        'lid_le': [71.5, '16/16'],
        'lid_gt': [71.5, 'boil0'],
        'pan_gt': [134, 'warm']
        },
    "boil0": {
        'T': 0,
        'T_gt': [1152, 'boil1'], #19'12"
        'pan_le': [120, '16/16'],
        'pan_gt': [120, 'boil1'],
        'pan_gt': [134, 'warm']
        },
    "boil1": {
        'T_gt': [1152, '10/16'],
        'T_gt': [2304, '7/16'], #38'24"
        'pan_le': [120, '16/16'],
        'pan_gt': [120, '10/16'],
        'pan_gt': [134, 'steam0']
        },
}
"""
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
"""