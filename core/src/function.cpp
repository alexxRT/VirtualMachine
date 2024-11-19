#include <vector>
#include <iostream>

template <typename T, class... Types>
class Function {
    Function(std::vector<int>& code, Types... args) {
        bytecode = code;

        // now need to know how to expand variodic template
    }

    // my template stack with various data type to be stored 
    T call(std::shared_ptr<stack> program_stack) {
        // push function arguments on stack
        for (auto& arg : arguments)
            program_stack->push(arg);

        // create frame
        Frame frame<T, Types>(program_stack, bytecode);
        // execute function bytecode
        T return_val = frame.execute_bytecode();

        // print execute status
        std::cout << "Function returned with exit code: [" << return_val  << "]" << std::endl;
    }

    void debug_print_args() {
        // same as in constructor for now
    }

    std::shared_ptr<Frame> frame;
    std::vector<int>& bytecode;
    std::vector<std::variant<Types>> arguments;
}