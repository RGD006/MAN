import firebase_admin
import json
from time import sleep

cred_obj = firebase_admin.credentials.Certificate('C:/What_needs_for_Vladick/MAN/Триангуляція/python/careful-form-371013-firebase-adminsdk-lijhc-bc6e9ac142.json')

default_app = firebase_admin.initialize_app(cred_obj, {
	'databaseURL': "https://careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app/"
	})

from firebase_admin import db

names = ["Test_1", "Test_2", "Test_3"]
RSSI_SIGNAL = []


while True:
    with open("coordinates.json", 'r') as file:
        json_file = []
        json_file = json.load(file)

        for el in names:
            RSSI_SIGNAL.append(db.reference(f"/signal_{el}"))

        for i in range(3):
            json_file[i].append(RSSI_SIGNAL[i].get()["RSSI"])

        print(json_file)

    with open("coordinates.json", "w") as file:
        json.dump(json_file, file, indent=4)

    sleep(30)