#!/usr/bin/python

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_table('result. dat', sep=' ', index_col = None, header = None)

plt.errorbar(df[0], df[1], df[2], marker = 'x', linestyle = 'None', color = 'k', label = 'simulation')
#plt.plot(np.arange(0.1, 0.96, 0.01), 1./(1. - np.arange(0.1, 0.96, 0.01)), marker = 'None', linestyle = '-', color = 'k', label = 'analytics')


r = np.arange(0.1, 0.96, 0.01)
ed = np.ones(86)
k=10
yplot = (ed-r)*r/(ed-r**(k+2))*(r**k+(ed-r**k*(k*(ed-r)+ed))/(ed-r)**2)+1
#yplot = (ed-r)*r/(ed-r**(k+2))*((ed-r**k*(k*(ed-r)+ed))/(ed-r)**2)
ref = r**(k+1)*(ed-r)/(ed-r**(k+2))
plt.plot(r, yplot, marker = 'None', linestyle = '-', color = 'g', label = 'analytics')
#plt.plot(r, ref, marker = 'None', linestyle = '-', color = 'g', label = 'analytics')


plt.xlabel(r'$\lambda / \mu$')
plt.ylabel('Average service time')
#plt.ylabel('Average waiting time')

plt.grid()
plt.legend(loc='best')
plt.savefig("service_time_M_myD_1_10.png")

