#include "machine.hpp"
#include "frame.hpp"
#include "builder.hpp"

using namespace VM;

void Machine::print_bytecode() {
    for (auto&& function : functions) {
        std::vector<int>::iterator code = function.bytecode.begin();
        while (code != function.bytecode.end()) {
            switch (*code) {
                case BYTECODE::IINC:
                    std::cout << std::format("{:#x}", *code) << " " << std::format("{:#x}", *(code + 1)) << " " << std::format("{:#x}", *(code + 2)) << " | "
                            << string_code.at(*code) << " " << std::format("{:#x}", *(code + 1)) << " " << std::format("{:#x}", *(code + 2)) << std::endl;
                    code += 3;
                break;
                case BYTECODE::CALL:
                case BYTECODE::ILOAD:
                case BYTECODE::ISTORE:
                case BYTECODE::BIPUSH:
                case BYTECODE::IF_ICMPEQ:
                case BYTECODE::IF_ICMPGE:
                case BYTECODE::IF_ICMPGT:
                case BYTECODE::IF_ICMPLE:
                case BYTECODE::IF_ICMPLT:
                case BYTECODE::IF_ICMPNE:
                case BYTECODE::GOTO:
                    std::cout << std::format("{:#x}", *code) << " " << std::format("{:#x}", *(code + 1)) << " | " 
                            << string_code.at(*code) << " " << std::format("{:#x}", *(code + 1)) << std::endl;
                    code += 2;
                break;
                default:
                    std::cout << std::format("{:#x}", *code) << " | " << string_code.at(*code) << std::endl; 
                    code ++;
            }
        }
    }
}

void Machine::print_stack() {
    std::cout << "---------------- Machine Stack in HEX ------------------" << std::endl;
    stack.print();
    std::cout << std::endl << std::endl;
}

void Machine::execute() {
    Frame main_frame{stack, variables_storage, functions[0], nullptr};
    main_frame.run_context(stack, functions[0].bytecode, functions);
};

void Machine::reset() {
    stack.clear();
    functions.clear();
};