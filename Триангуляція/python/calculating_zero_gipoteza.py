import math
from statistics import mean




points_of_anchors = [[10, 0], [4, 3], [0, 0]] # Test_1 Test_2 Test_3
points_of_placement = [[7, 2], [3, 1], [5, 2], [8, 1], [3,3]]
distance_zero_gipoteza = []

for anchor in points_of_anchors:
    for placement in points_of_placement:
        distance_zero_gipoteza.append([math.sqrt(pow((anchor[0] - placement[0]), 2) + pow((anchor[1] - placement[1]), 2))])




import json

with open("distance_from_anhors.json", "w") as file:
    json.dump(distance_zero_gipoteza, file, indent=4)
import matplotlib.pyplot as plt 



CONST_RSSI_SIGNAL = -52

def calculate_distance(rssi: int):
    return pow(10, (CONST_RSSI_SIGNAL + abs(rssi)) / (10 * 2.4))


rssi_signal_list = []
distance_from_rssi = []

with open("coordinates.json", "r") as file:
    rssi_signal_list = json.load(file)


# на кожну пару по 3 тести rssi-сигналу

for rssi_list in rssi_signal_list:
    temp_rssi = []
    for rssi in rssi_list:
        temp_rssi.append(calculate_distance(rssi))
    distance_from_rssi.append(temp_rssi)

print(distance_from_rssi)


