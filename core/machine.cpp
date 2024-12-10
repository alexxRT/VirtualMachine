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
                case BYTECODE::IIF_CMPEQ:
                case BYTECODE::IIF_CMPGE:
                case BYTECODE::IIF_CMPGT:
                case BYTECODE::IIF_CMPLE:
                case BYTECODE::IIF_CMPLT:
                case BYTECODE::IIF_CMPNE:
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
    // if (bytecode.size() == 0) {
    //     std::cout << "Nothing to execute! Please use load functions to load your programm!" << std::endl;
    //     return;
    // }

    if (functions.size() == 0 or entry_point >= functions.size()) {
        std::cout << "No entry point exists!" << std::endl;
        return;
    }

    Frame main_frame{&stack, functions[0], nullptr};
    main_frame.run_context(functions[0].bytecode, functions);
};

void Machine::reset() {
    stack.clear();
    functions.clear();
};