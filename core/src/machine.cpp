#include "function.hpp"
#include "stack.hpp"
#include "frame.hpp"
#include "builder.hpp"

namespace VM {
    class Machine {
        void load_fibanachi_cycled() {

        };

        void load_fibonachi_recursive() {

        };

        void execute() {
            if (bytecode.size() == 0) {
                std::cout << "Nothing to execute! Please use load functions to load your programm!" << std::endl;
                return;
            }

            if (functions.size() == 0 or entry_point >= functions.size()) {
                std::cout << "No entry point exists!" << std::endl;
                return;
            }

            size_t main_offset = functions[0].offset;

            Frame* main_frame = new Frame(&stack, functions, main_offset);
            main_frame->run_context(bytecode);
        };

        void reset() {
            entry_point = 0;
            bytecode.clear();
            stack.clear();
            functions.clear();
        }

        private:
            Stack stack;
            int entry_point;
            std::vector<int> bytecode;
            std::vector<Function> functions;
    };
};