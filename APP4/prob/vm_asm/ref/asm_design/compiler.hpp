#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <string>

namespace vm
{
    class Compiler
    {
    public:
        /// Create a parser/compiler/vm that can run the code.
        ///
        /// \param fname Source file, leave blank to use stdin.
        Compiler(const std::string& fname = std::string(""));

        // Run program once, does not reset registers.
        void run();
    };
}

#endif
