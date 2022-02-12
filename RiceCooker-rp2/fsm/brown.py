"""
mode - вывод имени режима
'start' - имя 1 состояния
LCD - вывод состояния
beep - t:N  (t ms) * (N раз )
T - уст. нач. времени
T_gt - если T > T_gt =>выполнить
pan_gt,pan_le - температура чаши
lid_gt,lid_le - температупа крышки
'state' - выполнение след. состояния
'end' - завершение и откл. нагревателей
'1/16' - выполнение регулировки мощности вкл/откл в сек.
"""
fsm={
    "mode": "Brown", # режим "коричневый рис"
    "start": {
        'LCD': 'PRE',
        'T': 0, #??
        'pan_gt': [[125,'warm'], [60, 'boil']],
        'T_gt': [[96, 'pre0']], 
        },
    "pre0": {
        'T':0,
        'T_gt': [[864, 'stand']], #14'24"
        'pan_le': [[50, '8/16']],
        'pan_gt': [[125, 'warm'],[50, '0/0']]
        },
    "pre1": {
        'T_gt': [[864, 'stand']],
        'pan_le': [[50, '3/16']],
        'pan_gt': [[125, 'warm'],[50, '0/0']],
        },
    "stand": {
        'LCD':'BOILING',
        'T':0,
        'T_gt': [[1536, 'boil1']], #25'36"
        'pan_le': [[82.9, '16/16']],
        'pan_gt': [[134, 'warm'],[82.9, 'weight']],
        },
    "weight": {
        'T':0,
        'T_gt': [[1536, 'boil1']],
        'lid_le': [[71.5, '16/16']],
        'lid_gt': [[71.5, 'boil0']],
        'pan_gt': [[134, 'warm']],
        },
    "boil0": {
        'T': 0,
        'T_gt': [[1152, 'boil1']], #19'12"
        'pan_le': [[120, '16/16']],
        'pan_gt': [[134, 'warm'],[120, 'boil1']],
        },
    "boil1": {
        'T_gt': [[1152, '10/16'],[2304, '7/16']], #38'24"
        'pan_le': [[120, '16/16']],
        'pan_gt': [[134, 'steam0'],[120, '10/16']],
        },
    "steam0": {
        'LCD': 'STEAM',
        'T': 0,
        'T_gt': [[0, '0/0'],[192, 'steam1']], #3'12"
        },
    "steam1": {
        'T': 0,
        'T_gt': [[0, '1/16'],[192, 'steam2']], #3'12"
        },
    "steam2": {
        'T': 0,
        'T_gt': [[0, '0/0'],[384, 'warm']], #6'24"
        },
    "warm": {
        'LCD': 'WARM',
        'beep': "500:8",
        'T': 0,
        'T_gt': [[43200, 'end']], #12hour
        'pan_le': [[71.5, '1/16']],
        'pan_gt': [[71.5, '0/0']],
        },
}
