#!/usr/bin/python

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import argparse
from scipy.special import factorial





def E_func(k, ro):
    sum2 = 1
    for j in range(0, k+1):
        sum2 -= ((1-ro)*((-ro*(k-j))**j)*np.exp(ro*(k-j))/factorial(j))
    return sum2

def service_time_for_d(lam, mu, n):
    n = int(n)

    ws = 1/lam/(1-E_func(n, lam/mu))*(np.sum([E_func(i, lam/mu) for i in range (1, n+1)])) + n/mu*(1-1/(1-E_func(n, lam/mu)))
    return ws



def b_n(n, ro) :
    sum = 0
    for i in range (int(n)+1):
        sum += (-1 * (n-i) * ro)**i/factorial(i) * np.exp((n-i)*ro)
    return sum

def pi_func(n, ro):
    n = int(n)
    if n==0:
        return 1-ro
    elif n == 1:
        return (1-ro)*(np.exp(ro)-1)

    sum1 = 0
    for k in range (1, n):
        sum1 += np.exp(k*ro)*((-1)**(n-k))*(((k*ro)**(n-k))/factorial(n-k) + ((k*ro)**(n-k-1))/factorial(n-k-1))

    sum1 += np.exp(n*ro)
    sum1 *= (1-ro)
    return sum1

def refused_prob(k, ro):
    k = int(k)
    if k > 50:
        sum2 = 0
        for i in range(1, k):
            sum2 += pi_func(i, ro)
        sum2 = 1 - sum2
    else :
        sum2 = 1
        for j in range(0, k+1):
            sum2 -= ((1-ro)*((-ro*(k-j))**j)*np.exp(ro*(k-j))/factorial(j))
    return (1-ro)*sum2/(1-ro*sum2)




parser = argparse.ArgumentParser()

parser.add_argument("k", type=float)
parser.add_argument("model", type=str)
parser.add_argument("service", type=str)

args = parser.parse_args()

k = args.k
model = args.model
service = args.service
file_name = "service_time_M_"+ model+"_1_"+str(int(k))+service+".png"
print(file_name + " will be created")


df=[0,0,0]
df[0] = pd.read_table('result_1dr-2.dat', sep=' ', index_col = None, header = None)
df[1] = pd.read_table('result_3dr-2.dat', sep=' ', index_col = None, header = None)
df[2] = pd.read_table('result_5dr-2.dat', sep=' ', index_col = None, header = None)
# print(df[1][3])
# print(df[0][3])

r = np.arange(0.001, 0.96, 0.01)
ed = np.ones(86)
plt.figure(figsize=(8,5))
if (model == 'm') :
    yplot = (1-r)*r/(1-r**(k+2))*(r**k+(1-r**k*(k*(1-r)+1))/(1-r)**2)+1
    ref = r**(k+1)*(ed-r)/(ed-r**(k+2))

else :
    ref = r/(2*(1-r))


if (service == "s"):

    i = 0
    color = ['g', 'r', 'b']
    for k in [1, 3, 5] :
        plt.plot(r, [service_time_for_d(x, 1, k)+1 for x in r], marker = 'None', linestyle = '-', color = color[i], label = 'analytics k={}'.format(k))
        plt.errorbar(df[i][0], df[i][1], df[i][2], marker = 'x', linestyle = 'None', color = color[i], label = 'simulation k={}'.format(k))
        i += 1

    plt.ylabel('Average service time')

elif (service == "r"): #refused
    i = 0
    color = ['g', 'r', 'b']
    for k in [1, 3, 5] :
        plt.plot(r, [refused_prob(k, x) for x in r], marker = 'None', linestyle = '-', color = color[i], label = 'analytics k={}'.format(k))
        plt.errorbar(df[i][0], df[i][3], df[i][4], marker = 'x', linestyle = 'None', color = color[i], label = 'simulation k={}'.format(k))
        plt.ylabel('Part of refused packets')
        i += 1
# else:
#     plt.plot(r, wait, marker = 'None', linestyle = '-', color = 'g', label = 'analytics')
#     plt.errorbar(df[0], df[5], df[6], marker = 'x', linestyle = 'None', color = 'k', label = 'simulation')
#     plt.ylabel('Average waiting time')




plt.xlabel(r'$\lambda / \mu$')

#plt.ylabel('Average waiting time')
plt.title('Model m/{}/1/1-3-5  '.format(model))
plt.grid()
# plt.yscale('log')
plt.legend(loc='best')
plt.savefig(file_name)


