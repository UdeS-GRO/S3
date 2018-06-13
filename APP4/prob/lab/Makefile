CPP=g++ -pthread --std=c++11 -g

targets=ex1 ex2 ex3

all: $(targets)

$(targets): %: %.cpp
	${CPP} -o $@ $<
