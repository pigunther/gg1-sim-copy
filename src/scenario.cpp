#include <iostream>
#include "packet-generator.h"
#include "simulator.h"

int main(int argc, char** argv)
{
  if (argc < 4) 
  {
    std::cout << "Usage: ./scenario seed lambda mu simTime" << std::endl;
    return -1;
  }
  int seed = atoi (argv[1]);
  double lambda = atof (argv[2]);
  double mu = atof (argv[3]);
  time_t simTime = atof (argv[4]);

  std::exponential_distribution<double>::param_type params1 (lambda);
  std::exponential_distribution<double>::param_type params2 (mu);
  PacketGenerator<std::exponential_distribution<double>, std::exponential_distribution<double>> gen(params1, params2);
  
  Simulator sim;
  sim.SetStop (simTime);
  sim.SetSeed (seed);

  gen.Start ();
  sim.Run ();
}