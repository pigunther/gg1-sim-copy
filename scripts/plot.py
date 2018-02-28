#!/usr/bin/python

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import argparse

parser = argparse.ArgumentParser()

parser.add_argument("k", type=float)
parser.add_argument("model", type=str)
parser.add_argument("service", type=str)

args = parser.parse_args()

#k=10 #don't forget to change k in variate_load.sh
#model = 'm'
#model = 'd'
#service = "s" #for all service time
#service = "r"
k = args.k
model = args.model
service = args.service
file_name = "service_time_M_"+ model+"_1_"+str(k)+service+".png"
print(file_name + " will be created")



df = pd.read_table('result.dat', sep=' ', index_col = None, header = None)

# plt.errorbar(df[0], df[1], df[2], marker = 'x', linestyle = 'None', color = 'k', label = 'simulation')
#plt.plot(np.arange(0.1, 0.96, 0.01), 1./(1. - np.arange(0.1, 0.96, 0.01)), marker = 'None', linestyle = '-', color = 'k', label = 'analytics')


r = np.arange(0.1, 0.96, 0.01)
ed = np.ones(86)
#yplot = (ed-r)*r/(ed-r**(k+2))*(r**k+(ed-r**k*(k*(ed-r)+ed))/(ed-r)**2)+1
#yplot = (ed-r)*r/(ed-r**(k+2))*((ed-r**k*(k*(ed-r)+ed))/(ed-r)**2)
#ref = r**(k+1)*(ed-r)/(ed-r**(k+2))
#plt.plot(r, ref, marker = 'None', linestyle = '-', color = 'g', label = 'analytics')

if (model == 'm') :
    #todo для модели M/M/1/k
    # yplot = (ed-r)*r/(ed-r**(k+2))*(r**k+(ed-r**k*(k*(ed-r)+ed))/(ed-r)**2)+1
    yplot = (1-r)*r/(1-r**(k+2))*(r**k+(1-r**k*(k*(1-r)+1))/(1-r)**2)+1
    ref = r**(k+1)*(ed-r)/(ed-r**(k+2))

else :
    #todo формулы для модели M/D/1/k
    #yplot = (ed-r)*r/(ed-r**(k+2))*(r**k+(ed-r**k*(k*(ed-r)+ed))/(ed-r)**2)+1
    yplot = 1+r/(2*(1-r))
    ref = r**(k+1)*(1-r)/(1-r**(k+2))


if (service == "s"):
    plt.plot(r, yplot, marker = 'None', linestyle = '-', color = 'g', label = 'analytics')
    plt.errorbar(df[0], df[1], df[2], marker = 'x', linestyle = 'None', color = 'k', label = 'simulation')
    plt.ylabel('Average service time')

else: #refused
    plt.plot(r, ref, marker = 'None', linestyle = '-', color = 'g', label = 'analytics')
    plt.errorbar(df[0], df[3], df[4], marker = 'x', linestyle = 'None', color = 'k', label = 'simulation')
    plt.ylabel('Part of refused packets')




plt.xlabel(r'$\lambda / \mu$')

#plt.ylabel('Average waiting time')
plt.title('Model m/{}/1/{}'.format(model, k))
plt.grid()
plt.legend(loc='best')
plt.savefig(file_name)

