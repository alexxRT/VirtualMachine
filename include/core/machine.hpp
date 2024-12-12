#pragma once
#include "function.hpp"
#include "stack.hpp"
#include "common.hpp"
#include "types.hpp"
#include <concepts>
#include <deque>

namespace VM {
    class Machine {
        public:
            template <std::convertible_to<Bytecode> BytecodeT>
            Machine(BytecodeT&& Functions, int stack_size = 10): 
                stack(stack_size),
                functions(std::forward<Bytecode>(Functions)) 
                {}

            void print_bytecode();
            void execute();
            void reset();
            void print_stack();

        private:
            Stack stack;
            std::deque<uint8_t> variables_storage;
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