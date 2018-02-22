#!/usr/bin/python

import subprocess
from scipy import stats
import argparse
import numpy as np

def parseArguments():
  parser = argparse.ArgumentParser()

  parser.add_argument("lambd", type=float)
  parser.add_argument("mu", type=float)
  parser.add_argument("simtime", type=float)
  parser.add_argument("--alpha", type=float, default=0.01)
  parser.add_argument("--beta", type=float, default=0.1)
  parser.add_argument("--runMode", type=str, default='static')

  return parser.parse_args()

def executeProgram(run, args):
  result = subprocess.Popen("../src/scenario {} {} {} {}".format(run, args.lambd, args.mu, args.simtime), 
            shell=True, stdout = subprocess.PIPE).stdout.read().split(" ")
  return float(result[1])

def confidenceInterval (serviceTimes, alpha, n):
  return np.sqrt(np.var(serviceTimes, ddof=1)) * stats.t.ppf(1-alpha/2, n-1) 

def main():
  args = parseArguments()

  serviceTimes = []
  
  if (args.runMode == "dynamic"):
    for run in range(1, 3):
      serviceTimes += [executeProgram(run, args)]
  
    run = 2
    while (confidenceInterval (serviceTimes, args.alpha, run) > args.beta):
      run = run + 1  
      serviceTimes += [executeProgram(run, args)]
  elif (args.runMode == "static"):
    for run in range(1, 11):
      serviceTimes += [executeProgram(run, args)]
  else:
    print ("Wrong runMode, variants: static dynamic")
    exit (1)
  print ("{} {} {}".format (args.lambd / args.mu, np.mean(serviceTimes), confidenceInterval(serviceTimes, args.alpha, run)) )

if __name__ == "__main__":
  main()