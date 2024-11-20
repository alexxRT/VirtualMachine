#include "function.hpp"
#include "stack.hpp"

namespace VM {
    class Machine {
        void load_fibanachi() {
            
        }


        private:
            Stack stack;
            int entry_point;
            std::vector<Function> functions;
    };
};