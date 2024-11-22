#include "function.hpp"
#include "stack.hpp"
#include "common.hpp"

namespace VM {
    class Machine {
        public:
            void load_fibanachi_cycled(int n);
            void load_fibonachi_recursive(int n);
            void print_bytecode();
            void execute();
            void reset();
            void print_stack();

        private:
            Stack stack;
            int entry_point;
            std::vector<int> bytecode;
            std::vector<Function> functions;
    };
};