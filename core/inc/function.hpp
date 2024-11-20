
#include "common.hpp"
#include "stack.hpp"
#include "frame.hpp"

namespace VM {
    class Function {
        Function(std::vector<int>& code) {
            bytecode = code;
        }

        // my template stack with various data type to be stored 
        void call(std::shared_ptr<Stack> program_stack) {
            // create frame
            Frame frame(program_stack, bytecode);
            // execute function bytecode
            frame.execute_bytecode();

            // print execute status
            std::cout << "Function returned with exit code: [" << return_val  << "]" << std::endl;
        }

        std::shared_ptr<Frame> frame;
        std::vector<int>& bytecode;
    };
};