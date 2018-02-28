cmake_minimum_required(VERSION 3.9)
project(gg1_simulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(gg1_simulator
        scripts/execute.py
        scripts/plot.py
        scripts/variate_load.sh
        src/makefile
        src/packet-generator.h
        src/packet.cpp
        src/packet.h
        src/packet.o
        src/queue.cpp
        src/queue.h
        src/queue.o
        src/scenario
        src/scenario.cpp
        src/scenario.o
        src/server.cpp
        src/server.h
        src/server.o
        src/simulator.cpp
        src/simulator.h
        src/simulator.o src/packet-generator.cpp src/const_distribution.cpp src/const_distribution.h)
