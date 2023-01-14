from sklearn.svm import SVC
import numpy as np
import json
import matplotlib.pyplot as plt
import math

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


# def return_distance_m(d: dict, SSID: str, SSID_id: int, SSID_it: int) -> float:
# 	return pow(10, (abs(d['RSSI']) - RSSI_coordinates[SSID_id][SSID][SSID_it]) / 150)


def return_distance_m(d: dict, SSID: str, SSID_id: int, SSID_it: int) -> float:
	return pow(10, (RSSI_coordinates[SSID_id][SSID][SSID_it] - d['RSSI']) / 10 * 2)


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
	return (pow(x, 2) + pow(y, 2) + pow(d_end, 2)) - (pow(x_y[-1]["x"], 2) + pow(x_y[-1]["y"], 2) + pow(d, 2))


def make_matrix2():
  for it in range(len(coordinates[:-2:])):
    temp_m = []
    for i in ['x', 'y']:
      temp_m.append(calc_matrix2(it, i))
    matrix2.append(temp_m)


make_matrix2()

x_y_d = {
	"Test": [],
	"Test2": [],
	"Vlad": []
}

print(distance_m)

end_coordinates = list()

for el in x_y[:-1:]:
	for d in distance_m[el["name"]]:
		temp = list()
		temp.append(el["x"])
		temp.append(el["y"])
		temp.append(d)
		x_y_d[el["name"]].append(temp)

for el in distance_m["Vlad"]:
	x_y_d["Vlad"].append(el)

for it in range(len(x_y_d["Test"])):
	temp = []
	for name in names_anchor[:-1:]:
		# print(x_y_d[name][it][0], x_y_d[name][it][1], x_y_d[name][it][2], x_y_d[names_anchor[-1]][it], 
		# calc_matrix1(x_y_d[name][it][0], x_y_d[name][it][1], x_y_d[name][it][2], x_y_d[names_anchor[-1]][it])
		temp.append(calc_matrix1(x_y_d[name][it][0], x_y_d[name][it][1], x_y_d[name][it][2], x_y_d[names_anchor[-1]][it]))
	matrix1.append(temp)

	matrix2_t = np.transpose(matrix2)
	matrix1_matrix2T = np.dot(matrix1, matrix2_t)
	matrix2_matrix2T = np.dot(matrix2_t, matrix2)

	inv_matrix2_matrix2T = np.linalg.inv(matrix2_matrix2T)

	# print(matrix1_matrix2T, matrix2_matrix2T, inv_matrix2_matrix2T, sep="\n")

	# print(np.dot(matrix1_matrix2T, inv_matrix2_matrix2T))
	end_coordinates.append(np.dot(matrix1_matrix2T, inv_matrix2_matrix2T))

	matrix1 = []

x = [x[0][0] for x in end_coordinates]
y = [y[0][1] for y in end_coordinates]

# print([coordinates[0]["x"], coordinates[1]["x"], coordinates[2]['x']] + x)
print(x, y, sep="\n")

a_point_x = np.array([coordinates[0]["x"], coordinates[1]["x"], coordinates[2]['x']])
a_point_y = np.array([coordinates[0]["y"], coordinates[1]["y"], coordinates[2]["y"]])

# 5, 2, 7
# 8, 2, 3

x_expected = [5,2,7]
y_expected = [8,2,3]

x_point = np.array(x)
y_point = np.array(y)

plt.plot(a_point_x, a_point_y, '^', ms = 10)
plt.plot(x_point, y_point, 'o', ms = 5)
plt.plot(x_expected, y_expected, '*', ms= 7)
plt.show()