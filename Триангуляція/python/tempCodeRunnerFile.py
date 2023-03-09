import firebase_admin
import json
from time import sleep

cred_obj = firebase_admin.credentials.Certificate('C:/What_needs_for_Vladick/MAN/Триангуляція/python/careful-form-371013-firebase-adminsdk-lijhc-bc6e9ac142.json')

default_app = firebase_admin.initialize_app(cred_obj, {
	'databaseURL': "https://careful-form-371013-default-rtdb.europe-west1.firebasedatabase.app/"
	})

from firebase_admin import db