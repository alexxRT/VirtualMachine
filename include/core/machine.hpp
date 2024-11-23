#pragma once
#include "function.hpp"
#include "stack.hpp"
#include "common.hpp"

namespace VM {
    class Machine {
        public:
            Machine(const int stack_size = 10): stack(stack_size) {
                bytecode = std::make_shared<std::vector<int>>();
            };
            void load_fibanachi_cycled(int n);
            void load_fibonachi_recursive(int n);
            void print_bytecode();
            void execute();
            void reset();
            void print_stack();

        private:
            Stack  stack;
            static const size_t entry_point = 0;
            std::shared_ptr<std::vector<int>> bytecode;
            std::vector<Function> functions;
    };
};