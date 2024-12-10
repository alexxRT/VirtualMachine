#pragma once
#include "function.hpp"
#include "stack.hpp"
#include "common.hpp"
#include "types.hpp"
#include <concepts>

namespace VM {
    class Machine {
        public:
            template <std::convertible_to<Bytecode> BytecodeT>
            Machine(BytecodeT&& Functions, int stack_size = 10): 
                stack(stack_size),
                functions(std::forward<Bytecode>(Functions)) 
                {}

            void load_fibanachi_cycled(int n);
            void load_fibonachi_recursive(int n);
            void print_bytecode();
            void execute();
            void reset();
            void print_stack();

        private:
            Stack  stack;
            static const size_t entry_point = 0;
            Bytecode functions;
    };

    template <std::convertible_to<Bytecode> BytecodeT>
    void Execute(BytecodeT&& bytecode) {
        Machine jvm {std::forward<Bytecode>(bytecode)};
        jvm.print_bytecode();
        jvm.execute();
        jvm.print_stack();
    }   
};