import pyrebase
import json
from time import sleep
# [
#   { 
#     "x": 1,
#     "y": 1,
#     "RSSI A": -51
#   },
#   {
#     "x": 200,
#     "y": 1,
#     "RSSI A": -61
#   },
#   {
#     "x": 100,
#     "y": 150,
#     "RSSI A": -44
#   },
#   {
    
#   }
# ]



while True:
  with open("coordinates.json", 'r') as file:
    i = 0

    config = {
      "apiKey": "MUFMetUYRPm1Dx09JbHSJD34vNNBuc8D3o6PgMI0",
      "authDomain": "projectId.firebaseapp.com",
      "databaseURL": "https://careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app/",
      "storageBucket": "projectId.appspot.com"
    }
    
    firebase = pyrebase.initialize_app(config)
    db = firebase.database()
    user = db.get()

    list_of_anchors_signal = [network.val() for network in user.each()]

    json_file = []
  
    print(list_of_anchors_signal, end="\n\n\n")
    json_file = json.load(file)
    for network in list_of_anchors_signal:
      json_file[-1][i][network["SSID"]].append(network["RSSI"])
      i += 1
    with open("coordinates.json", "w") as file:
      json.dump(json_file, file, indent=4)
    
  sleep(10)



