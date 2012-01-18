CC=gcc
CXX=g++
CFLAGS=$(O) 
CXXFLAGS=$(CFLAGS) --std=c++0x
O=-O2
LFLAGS=-lm
OBJS=objs/Population.o objs/EvolFunctions.o objs/EvolException.o objs/Subject.o

all: Plecak PlecakDuo BMITest 

BMITest: $(OBJS) objs/BMITest.o
	@ echo "    LINK ./BMIT"
	@ $(CXX) $(LFLAGS) $(OBJS) objs/BMITest.o -o "./BMI"

Plecak: $(OBJS) objs/Plecak.o
	@ echo "    LINK ./Plecak"
	@ $(CXX) $(LFLAGS) $(OBJS) objs/Plecak.o -o "./Plecak"

PlecakDuo: $(OBJS) objs/PlecakDuo.o
	@ echo "    LINK ./PlecakDuo"
	@ $(CXX) $(LFLAGS) $(OBJS) objs/PlecakDuo.o -o "./PlecakDuo"

objs/Population.o: src/Population.cpp src/Population.hpp src/Subject.hpp src/EvolException.hpp src/Chromosome.hpp src/debug.h src/Observer.hpp src/EvolFunctions.hpp
	@ echo "    CXX  ./src/Population.cpp"
	@ $(CXX) $(CXXFLAGS) -c "./src/Population.cpp" -o $@

objs/EvolFunctions.o: src/EvolFunctions.cpp src/EvolFunctions.hpp
	@ echo "    CXX  ./src/EvolFunctions.cpp"
	@ $(CXX) $(CXXFLAGS) -c "./src/EvolFunctions.cpp" -o $@

objs/EvolException.o: src/EvolException.cpp src/EvolException.hpp
	@ echo "    CXX  ./src/EvolException.cpp"
	@ $(CXX) $(CXXFLAGS) -c "./src/EvolException.cpp" -o $@

objs/Subject.o: src/Subject.cpp src/Subject.hpp src/EvolException.hpp src/Chromosome.hpp src/debug.h
	@ echo "    CXX  ./src/Subject.cpp"
	@ $(CXX) $(CXXFLAGS) -c "./src/Subject.cpp" -o $@

objs/BMITest.o: src/BMITest.cpp src/debug.h src/Population.hpp src/Subject.hpp \
 src/EvolException.hpp src/Chromosome.hpp src/Observer.hpp src/EvolFunctions.hpp
	@ echo "    CXX  ./src/BMITest.cpp"
	@ $(CXX) $(CXXFLAGS) -c "./src/BMITest.cpp" -o $@

objs/Plecak.o: src/Plecak.cpp src/debug.h src/Population.hpp src/Subject.hpp \
 src/EvolException.hpp src/Chromosome.hpp src/Observer.hpp src/EvolFunctions.hpp
	@ echo "    CXX  ./src/Plecak.cpp"
	@ $(CXX) $(CXXFLAGS) -c "./src/Plecak.cpp" -o $@

objs/PlecakDuo.o: src/PlecakDuo.cpp src/debug.h src/Population.hpp src/Subject.hpp \
 src/EvolException.hpp src/Chromosome.hpp src/Observer.hpp src/EvolFunctions.hpp
	@ echo "    CXX  ./src/PlecakDuo.cpp"
	@ $(CXX) $(CXXFLAGS) -c "./src/PlecakDuo.cpp" -o $@

clean:
	@ rm objs/*.o

