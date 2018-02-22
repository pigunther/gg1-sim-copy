CXX=g++
INCLUDES=./
CXXFLAGS=-Wall -O3 -g -std=c++11

scenario : scenario.o simulator.o queue.o packet.o
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -o scenario scenario.o simulator.o queue.o packet.o

test_random.o : test_random.cpp packet-generator.h simulator.h
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -c test_random.cpp
 
queue.o: queue.cpp queue.h packet.h simulator.h
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -c queue.cpp 

simulator.o: simulator.cpp simulator.h
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -c simulator.cpp

packet.o: packet.cpp packet.h
	$(CXX) $(CXXFLAGS) -L$(INCLUDES) -c packet.cpp

clean:
	rm -rf *.o scenario

