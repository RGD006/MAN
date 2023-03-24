import firebase_admin
import json

cred_obj = firebase_admin.credentials.Certificate('F:\\Projects\\MAN\\Триангуляція\\python\\careful-form-371013-firebase-adminsdk-lijhc-bc6e9ac142.json')

default_app = firebase_admin.initialize_app(cred_obj, {
	'databaseURL': "https://careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app/"
	})

from firebase_admin import db

names = ["Test_1", "Test_2", "Test_3"]
RSSI_SIGNAL = []
ref = db.reference("Value_Trio")

with open("coordinates.json", "w") as file:
    temp_1 = []
    temp_2 = []
    temp_3 = []
    for i in range(1, len(ref.get()) + 1):
        temp_1.append(ref.get()["Pair" + str(i)]["Test_1"]) # type: ignore
        temp_2.append(ref.get()["Pair" + str(i)]["Test_2"]) # type: ignore
        temp_3.append(ref.get()["Pair" + str(i)]["Test_3"]) # type: ignore
    RSSI_SIGNAL.append(temp_1)
    RSSI_SIGNAL.append(temp_2)
    RSSI_SIGNAL.append(temp_3)

    json.dump(RSSI_SIGNAL, file, indent=4)