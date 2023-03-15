import numpy as np
import json
import matplotlib.pyplot as plt


# порядок точок доступу
# Test
# Test2
# Vlad

coord_x = [10, 0, 4]
coord_y = [0, 0, 3]

last_x = 4
last_y = 1

RSSI_CONST_TEST = -52

def calc_d(test_1, test_2, test_3):
  res = []
  res.append(pow(10, (RSSI_CONST_TEST + abs(test_1)) / (10 * 2.4)))
  res.append(pow(10, (RSSI_CONST_TEST + abs(test_2)) / (10 * 2.4)))
  res.append(pow(10, (RSSI_CONST_TEST + abs(test_3)) / (10 * 2.4)))
  return res

l = calc_d(-65, -58, -47)

DISTANCE_FROM_RSSI = []

with open("coordinates.json", "r") as file:
  RSSI_L = json.load(file)
  for i in range(len(RSSI_L[0])):
    DISTANCE_FROM_RSSI.append(calc_d(RSSI_L[0][i], RSSI_L[1][i], RSSI_L[2][i]))


MATRIX2 = [[2 * (1 - 4), 2 * (10 - 1)]
          ,[2 * (10 - 4), 2 * (10 - 1)]]


matrix1_test = [[pow(coord_x[0], 2) + pow(coord_y[0], 2) - pow(last_x, 2) - pow(last_y, 2) - pow(l[0], 2) + pow(l[-1], 2)],
                [pow(coord_x[1], 2) + pow(coord_y[1], 2) - pow(last_y, 2) - pow(last_y, 2) - pow(l[1], 2) + pow(l[-1], 2)]]


def calc_matrix1(l_distance):
    matrix1 = [[pow(coord_x[0], 2) + pow(coord_y[0], 2) - pow(last_x, 2) - pow(last_y, 2) - pow(l_distance[0], 2) + pow(l_distance[-1], 2)],
               [pow(coord_x[1], 2) + pow(coord_y[1], 2) - pow(last_y, 2) - pow(last_y, 2) - pow(l_distance[1], 2) + pow(l_distance[-1], 2)]]
    return matrix1

# print(matrix1_test, calc_matrix1(DISTANCE_FROM_RSSI[0]), sep="\n\n\n")


MATRIX_TO_CALCULATE = []

for distance in DISTANCE_FROM_RSSI:
  MATRIX_TO_CALCULATE.append(calc_matrix1(distance))


MATRIX2_T = np.transpose(MATRIX2)
matrix2_matrix2T = np.dot(MATRIX2_T, MATRIX2)
inv_matrix2_matrix2T = np.linalg.inv(matrix2_matrix2T)


RESULT_TO_MODEL = []

for matrix in MATRIX_TO_CALCULATE:
  matrix_matrix2T = np.dot(MATRIX2_T, matrix)
  RESULT_TO_MODEL.append(np.dot(inv_matrix2_matrix2T, matrix_matrix2T))

x_expected = [7,3,5,8,3]
y_expected = [2,1,2,1,3]


x_res = []
y_res = []

b1x_res = []
b1y_res = []
b2x_res = []
b2y_res = []
lx_res = []
ly_res = []

for el in RESULT_TO_MODEL:
  x_res.append(*el[0])
  y_res.append(*el[1])

# print(x_res, y_res, sep="\n\n\n")

# plt.plot(x_expected, y_expected, "*")
plt.plot([10, 0, 4], [0, 0, 3], "^")

for i in range(len(x_res)):
    if i <= 6:
       b2x_res.append(x_res[i])
       b2y_res.append(y_res[i])
    elif 6 < i <= 12:
       lx_res.append(x_res[i])
       ly_res.append(y_res[i])        
    else:
        b1x_res.append(x_res[i])
        b1y_res.append(y_res[i])

plt.scatter(b1x_res, b1y_res, 50)
plt.scatter(b2x_res, b2y_res, 50)
plt.scatter(lx_res, ly_res, 50)
plt.scatter(x_expected, y_expected, 50)
plt.show()

