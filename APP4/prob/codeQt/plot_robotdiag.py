#!/usr/bin/env python

import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("/tmp/robotdiag.csv", delimiter=";", skip_header=1);

# Column indices
ID  = 0
T   = 1
POS = 2

m1 = data[data[:,ID]==1]
m2 = data[data[:,ID]==2]

plt.plot(m1[:, T], m1[:, POS], "r")
plt.plot(m2[:, T], m2[:, POS], "b")

plt.show()
