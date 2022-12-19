from sklearn.svm import SVC
import numpy as np
import json

# JSON parameters
# 1st anchor Test
# 2nd anchor Test2
# 3d anchor Vlad

distance_m = {
		"Test": [],
		"Test2": [],
		"Vlad": []
}


coordinates = []


def return_distance_m(d: dict, SSID: str, SSID_id: int, SSID_it: int) -> float:
	return pow(10, ((d['RSSI'] - RSSI_coordinates[SSID_id][SSID][SSID_it])) / 20)


def calc_matrix2(it_coord: int, x_y: str):
	return 2 * (coordinates[it_coord][x_y] - coordinates[-2][x_y])


with open("coordinates.json", 'r') as coord:
	coordinates = json.load(coord)


anchor_RSSI = coordinates[:-1:]
RSSI_coordinates = coordinates[-1]
names_anchor = []

for el in RSSI_coordinates:
		 names_anchor.append(list(el.keys())[-1])

for anchor in range(len(anchor_RSSI)): # знаходження відстані від точки WiFi (або d по формулі з KW36 Localization Based on RSSI Ranging Application)
		for i in range(len(RSSI_coordinates[anchor][names_anchor[anchor]])):
				distance_m[names_anchor[anchor]].append(return_distance_m(anchor_RSSI[anchor], names_anchor[anchor], anchor, i))


matrix1 = []
matrix2 = []
x_y = [{'name': el["name"],"x": el["x"],"y": el["y"]} for el in coordinates[:-1:]]

def calc_matrix1(x, y, d, d_end) -> float:
	return (x ** 2 + y ** 2 + d_end ** 2) - (x_y[-1]["x"] ** 2 + x_y[-1]["y"] ** 2 + d ** 2)


def make_matrix2():
  for it in range(len(coordinates[:-2:])):
    temp_m = []
    for i in ['x', 'y']:
      temp_m.append(calc_matrix2(it, i))
    matrix2.append(temp_m)


make_matrix2()

end_data = {
	"Test": [],
	"Test2": [],
	"Vlad": []
}

for el in x_y[:-1:]:
	for d in distance_m[el["name"]]:
		temp = list()
		temp.append(el["x"])
		temp.append(el["y"])
		temp.append(d)
		end_data[el["name"]].append(temp)

for el in distance_m["Vlad"]:
	end_data["Vlad"].append(el)

for it in range(len(end_data["Test"])):
	temp = []
	for name in names_anchor[:-1:]:
		print(end_data[name][it][0], end_data[name][it][1], end_data[name][it][2], end_data[names_anchor[-1]][it])
		temp.append(calc_matrix1(end_data[name][it][0], end_data[name][it][1], end_data[name][it][2], end_data[names_anchor[-1]][it]))
	matrix1.append(temp)

  

	matrix1 = []
