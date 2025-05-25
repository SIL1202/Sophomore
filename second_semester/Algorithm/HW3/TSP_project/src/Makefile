CXX = clang++
CXXFLAGS = -std=c++17 -Wall -O2

SRC = tsp_solver.cpp tsp_fast_algorithms.cpp tsp_metaheuristics.cpp
HDR = tsp_solver.h tsp_fast_algorithms.h tsp_metaheuristics.h

all: main tsp_special

main: main.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o main main.cpp $(SRC)

tsp_special: tsp_special_case_main.cpp $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) -o tsp_special tsp_special_case_main.cpp $(SRC)

clean:
	rm -f main tsp_special
