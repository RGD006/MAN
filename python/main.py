from sklearn.svm import SVC
import numpy as np
import threading
import json

RSSI_distant = []

logs_RSSI = open("putty.txt", "r")

with json.loads("coordinates.json") as coord:
  for el in logs_RSSI:
    pass

logs_RSSI.close()
