import pyrebase
import json
from time import sleep
import csv


# while True:
#   with open("coordinates.json", 'r') as file:
#     i = 0

#     config = {
#       "apiKey": "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0",
#       "authDomain": "projectId.firebaseapp.com",
#       "databaseURL": "https://careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app/",
#       "storageBucket": "projectId.appspot.com"
#     }
    
#     firebase = pyrebase.initialize_app(config)
#     db = firebase.database()
#     user = db.get()

#     list_of_anchors_signal = [network.val() for network in user.each()]

#     json_file = []
  
#     print(list_of_anchors_signal, end="\n\n\n")
#     json_file = json.load(file)
#     for network in list_of_anchors_signal:
#       json_file[-1][i][network["SSID"]].append(network["RSSI"])
#       i += 1
#     with open("coordinates.json", "w") as file:
#       json.dump(json_file, file, indent=4)
    
#   sleep(10)

config = {
  "apiKey": "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0",
  "authDomain": "projectId.firebaseapp.com",
  "databaseURL": "https://careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app/",
  "storageBucket": "projectId.appspot.com"
}
    
firebase = pyrebase.initialize_app(config)
db = firebase.database()
user = db.get()

list_of_anchors_signal = [network.val() for network in user.each()][1]

pair = list()

for i in range(len(list_of_anchors_signal)):
  temp_l = list()
  # print(list_of_anchors_signal["Pair_" + str(i)])
  for el in list_of_anchors_signal["Pair_" + str(i)].items():
    temp_l.append(el[1])
  pair.append(temp_l)


with open("coord.csv", "w", newline='') as csvfile:
  spawnwriter = csv.writer(csvfile, delimiter= ' ', quotechar= "|", quoting=csv.QUOTE_MINIMAL)

  for coord in pair:
    spawnwriter.writerow(coord)

# print(pair)


