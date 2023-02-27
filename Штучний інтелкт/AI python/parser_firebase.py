import firebase_admin
import json

cred_obj = firebase_admin.credentials.Certificate('C:/What_needs_for_Vladick/MAN/Триангуляція/python/careful-form-371013-firebase-adminsdk-lijhc-bc6e9ac142.json')

default_app = firebase_admin.initialize_app(cred_obj, {
	'databaseURL': "https://careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app/"
	})

from firebase_admin import db
import csv

ref = db.reference("/Value")

pair = []

for i in range(len(ref.get())):
    temp = []
    for el in ref.get()["Pair_" + str(i)].items():
        temp.append(el[1])
    pair.append(temp)

with open("coord.csv", "w", newline='') as csvfile:
  spawnwriter = csv.writer(csvfile, delimiter= ' ', quotechar= "|", quoting=csv.QUOTE_MINIMAL)

  for coord in pair:
    spawnwriter.writerow(coord)
 
print("END")