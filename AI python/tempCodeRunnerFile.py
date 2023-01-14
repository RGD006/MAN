X, y = features[:, :-1], features[:, -1]
# classifier = SVC(kernel='linear').fit(X, y)
# c_code = port(classifier, classmap=classmap)
# print(c_code)