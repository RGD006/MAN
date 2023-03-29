import numpy as np
from glob import glob
from os.path import basename

from sklearn.svm import SVC
from micromlgen import port


def load_features(folder):
    dataset = None
    classmap = {}
    for class_idx, filename in enumerate(glob('%s/*.csv' % folder)):
        class_name = basename(filename)[:-4]
        classmap[class_idx] = class_name
        samples = np.loadtxt(filename, dtype=float, delimiter=' ')
        labels = np.ones((len(samples), 1)) * class_idx
        samples = np.hstack((samples, labels))
        dataset = samples if dataset is None else np.vstack((dataset, samples))

    return dataset, classmap

features, classmap = load_features('F:/Projects/MAN/Штучний інтелкт/AI python/classification')
X, y = features[:, :-1], features[:, -1]

from sklearn.ensemble import RandomForestClassifier

def get_classifier(features):
    X, y = features[:, :-1], features[:, -1]

    return RandomForestClassifier(20, max_depth=10).fit(X, y)

classifier = get_classifier(features)
c_code = port(classifier, classmap=classmap)
print(c_code)