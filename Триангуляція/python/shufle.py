import random
import json

list_of_RSSI_signal = []
pairs_of_RSSI = []

with open("coordinates.json", 'r') as file:
    list_of_RSSI_signal = json.load(file)
    
    for i in range(len(list_of_RSSI_signal[0])):
        temp = []
        for j in range(3):
            temp.append(list_of_RSSI_signal[j][i])
        temp.append(i)
        pairs_of_RSSI.append(temp)

# for el in pairs_of_RSSI:
#     if el[-1] <= 6:
#         el[-1] = "bedroom 1"
#     elif 6 < el[-1] <= 12:
#         el[-1] = "living room"
#     else:
#         el[-1] = "bedroom 2"

# shufle = []

print(pairs_of_RSSI)

