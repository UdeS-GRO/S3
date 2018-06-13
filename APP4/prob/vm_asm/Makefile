CPP=g++ -pthread --std=c++11 -g

HEADERS=ast.hpp compiler.hpp parser.hpp vm.hpp
VM_SRCS=compiler.cpp ast.cpp parser.cpp tokens.cpp vm.cpp

machine: machine.cpp ${VM_SRCS} ${HEADERS}
	${CPP} -o machine machine.cpp ${VM_SRCS}


