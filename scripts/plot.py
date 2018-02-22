#!/usr/bin/python

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_table("result.dat", sep=' ', index_col = None, header = None)
plt.errorbar(df[0], df[1], df[2], marker = 'x', linestyle = 'None', color = 'k', label = 'simulation')
plt.plot(np.arange(0.1, 0.96, 0.01), 1./(1. - np.arange(0.1, 0.96, 0.01)), marker = 'None', linestyle = '-', color = 'k', label = 'analytics')
plt.xlabel(r'$\lambda / \mu$')
plt.ylabel('Average service time')
plt.grid()
plt.legend(loc='best')
plt.savefig("service_time.png")

