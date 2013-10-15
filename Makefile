toCompile =	jacobi.c

CXX = gcc

CXXFLAGS = -g -Wall -std=c99 -lm -O3

all: jacobi

%.o: %.c
	$(CXX) $(CXXFLAGS) -c $<

jacobi: $(toCompile)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	$(RM) *.o 
