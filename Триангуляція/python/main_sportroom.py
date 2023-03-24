import numpy as np
import matplotlib.pyplot as plt

cordinates_anchors = [[10, 0], 
                      [4, 3], 
                      [0, 0]]

distance_to_anchor = [[2.035324769, 4.206377714, 5.869935103], 
                      [1.778802047, 3.962932043, 5.403079506], 
                      [6.195442874, 2.443741104, 3.877733363], 
                      [4.828086209, 3.59084822, 6.104716706], 
                      [4.804595065, 3.592308964, 4.059122898]]


res_cord = []

# matrix_A = np.matrix([[2 * (cordinates_anchors[0][0] - cordinates_anchors[-1][0]), 2 * (cordinates_anchors[0][1] - cordinates_anchors[-1][1])],
#                       [2 * (cordinates_anchors[1][0] - cordinates_anchors[-1][0]), 2 * (cordinates_anchors[1][0] - cordinates_anchors[-1][1])]])

# matrix_A_T = matrix_A.transpose()
# matrix_A_T_inv = np.linalg.inv(np.dot(matrix_A_T, matrix_A))

# for array in distance_to_anchor:
#     matrix_B = [[pow(cordinates_anchors[0][0], 2) + pow(cordinates_anchors[0][1], 2) - pow(cordinates_anchors[-1][0], 2) - pow(cordinates_anchors[-1][1], 2) - pow(array[0], 2) + pow(array[-1], 2)], # type: ignore
#                 [pow(cordinates_anchors[1][0], 2) + pow(cordinates_anchors[1][1], 2) - pow(cordinates_anchors[-1][0], 2) - pow(cordinates_anchors[-1][1], 2) - pow(array[1], 2) + pow(array[-1], 2)]] # type: ignore
#     res_cord.append(np.dot(matrix_A_T_inv, np.dot(matrix_A_T, matrix_B)))




from easy_trilateration.model import Circle
from easy_trilateration.least_squares import easy_least_squares  

for distance in distance_to_anchor:
    arr = [Circle(cordinates_anchors[0][0], cordinates_anchors[0][1], distance[0]),
           Circle(cordinates_anchors[1][0], cordinates_anchors[1][1], distance[1]),
           Circle(cordinates_anchors[2][0], cordinates_anchors[2][1], distance[2])]
    result, meta = easy_least_squares(arr)
    res_cord.append([result.center.x, result.center.y])


for el in res_cord:
    print(el)

plt.scatter([el[0] for el in cordinates_anchors], [el[1] for el in cordinates_anchors], 100, marker="^") # type: ignore

plt.scatter(res_cord[0][0], abs(res_cord[0][1]), 100, color="g")
plt.scatter(res_cord[1][0], abs(res_cord[1][1]), 100, color="b")
plt.scatter(res_cord[2][0], abs(res_cord[2][1]), 100, color="r")
plt.scatter(res_cord[3][0], abs(res_cord[3][1]), 100, color="y")
plt.scatter(res_cord[4][0], abs(res_cord[4][1]), 100, color="c")
plt.scatter(7, 2, 100, color="g", marker="*") # type: ignore 
plt.scatter(3, 1, 100, color="b", marker="*") # type: ignore
plt.scatter(5, 2, 100, color="r", marker="*") # type: ignore
plt.scatter(8, 1, 100, color="y", marker="*") # type: ignore
plt.scatter(3, 3, 100, color="c", marker="*") # type: ignore


plt.grid()
plt.show()
