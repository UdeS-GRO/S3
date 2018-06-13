#include "compiler.hpp"
#include "vm.hpp"

int main(int argc, char** argv)
{
    using namespace vm;

    std::string fname;

    if (argc >= 2) {
        fname = std::string(argv[1]);
    }

    Compiler c(fname);

    c.run();

    printf("Registers: \n");
    for (int i = 0; i < 4; ++i) {
        printf("R%d: %f\n", i + 1, CPU::registers[i]);
    }

    return 0;
}

