#include <iostream>

#include "ast.hpp"
#include "vm.hpp"

using namespace vm;

void Expression::run()
{
    printf("NOP\n");
}
Exp_2R::Exp_2R(Register r1, Register r2):
    r1_(r1), r2_(r2)
{
}

Exp_ADD::Exp_ADD(Register r1, Register r2): Exp_2R(r1, r2)
{}

void Exp_ADD::run()
{
    using namespace vm;
    CPU::registers[r1_] = CPU::registers[r1_] + CPU::registers[r2_];
}

Exp_SUB::Exp_SUB(Register r1, Register r2): Exp_2R(r1, r2)
{}

void Exp_SUB::run()
{
    using namespace vm;
    CPU::registers[r1_] = CPU::registers[r1_] - CPU::registers[r2_];
}

Exp_MUL::Exp_MUL(Register r1, Register r2): Exp_2R(r1, r2)
{}

void Exp_MUL::run()
{
    using namespace vm;
    CPU::registers[r1_] = CPU::registers[r1_] * CPU::registers[r2_];
}

Exp_DIV::Exp_DIV(Register r1, Register r2): Exp_2R(r1, r2)
{}

void Exp_DIV::run()
{
    using namespace vm;
    CPU::registers[r1_] = CPU::registers[r1_] / CPU::registers[r2_];
}

Exp_LDA::Exp_LDA(Register r1, const std::string& addr):
    r1_(r1),
    addr_(addr)
{}

void Exp_LDA::run()
{
    using namespace vm;

    Memory::iterator i = CPU::memory.find(addr_);
    if (i == CPU::memory.end()) {
        std::cerr   << "Runtime error: Adress undefined: " 
                    << addr_ << std::endl;
        return;
    }

    CPU::registers[r1_] = i->second;
}

Exp_STO::Exp_STO(const std::string& addr, Register r1):
    addr_(addr),
    r1_(r1)
{}

void Exp_STO::run()
{
    using namespace vm;

    CPU::memory[addr_] = CPU::registers[r1_];
}


Exp_LDC::Exp_LDC(Register r1, float val):
    r1_(r1),
    val_(val)
{}

void Exp_LDC::run()
{
    using namespace vm;

    CPU::registers[r1_] = val_;
}

vm::Expressions& vm::prog()
{
    static Expressions prog_;

    return prog_;
}
