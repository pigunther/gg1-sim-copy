#include <iostream>
#include <memory>
#include "packet-generator.h"
#include "simulator.h"
#include "const_distribution.h"

int main(int argc, char** argv) {
  if (argc < 4) {
    std::cout << "Usage: ./scenario seed lambda mu simTime queueLen" << std::endl;
    return -1;
  }
  int seed = atoi (argv[1]);
  double lambda = atof (argv[2]);
  double mu = atof (argv[3]);
  time_t simTime = atof (argv[4]);
    unsigned int k = atoi(argv[5]);

  std::exponential_distribution<double>::param_type params1 (lambda);
  std::exponential_distribution<double>::param_type params2 (mu);
  //PacketGenerator<std::exponential_distribution<double>, std::exponential_distribution<double>> packetGen(params1, params2);

  //std::uniform_real_distribution<double> d1(0.0,1/mu);
//  PacketGenerator<std::exponential_distribution<double>, std::uniform_real_distribution<double>> packetGen(params1, d1.param());
  PacketGenerator<std::exponential_distribution<double>, const_distribution<double>> packetGen(params1, mu);


  std::shared_ptr<Queue> new_queue(new Queue(k));

  std::shared_ptr<Server> server (new Server (new_queue));

  packetGen.SetServer (server);  
  
  Simulator sim;
  sim.SetStop (simTime);
  sim.SetSeed (seed);

  packetGen.Start ();
  sim.Run ();
}
