#include "machine.hpp"
#include "frame.hpp"
#include "builder.hpp"

using namespace VM;

// void Machine::load_fibanachi_cycled(int n) {
//     Builder build(bytecode);
//     //fib(n)
//     build._BIPUSH_(0);          // 0
//     build._ISTORE_1();          // 2
//     build._BIPUSH_(1);          // 3
//     build._ISTORE_2();          // 5
//     build._BIPUSH_(0);          // 6
//     build._ISTORE_3();          // 8
//     build._ILOAD_3();           // 9
//     build._ILOAD_0();           // 10
//     build._IF_ICMPGE_(28);      // 11
//     build._ILOAD_1();           // 13
//     build._ILOAD_2();           // 14
//     build._IADD_();             // 15
//     build._ISTORE_(4);          // 16
//     build._ILOAD_2();           // 18
//     build._ISTORE_1();          // 19
//     build._ILOAD_(4);           // 20
//     build._ISTORE_2();          // 22
//     build._IINC_(3, 1);         // 23
//     build._GOTO_(9);            // 26
//     build._ILOAD_2();           // 28
//     build._RETURN_();           // 29

//     size_t main_offset = bytecode->size();

//     // main()
//     build._BIPUSH_(n);          // 30
//     build._CALL_(1);            // 32
//     build._RETURN_();           // 34

//     // add main(): // main allways has entrance point in zero
//     // 0 - main, 1 - fibanachi
//     Function MAIN(main_offset);
//     functions.push_back(MAIN);

//     // add fib(int):
//     Function FIB(0, static_cast<int>(0));
//     functions.push_back(FIB);
// };

// void Machine::load_fibonachi_recursive(int n) {
//     Builder build(bytecode);
//     // fib(n)
//     build._ILOAD_0();           // 0
//     build._BIPUSH_(1);          // 1
//     build._IF_ICMPGT_(7);       // 3
//     build._ILOAD_0();           // 5
//     build._RETURN_();           // 6
//     build._ILOAD_0();           // 7
//     build._BIPUSH_(1);          // 8
//     build._ISUB_();             // 10
//     build._CALL_(1);            // 11
//     build._ILOAD_0();           // 13
//     build._BIPUSH_(2);          // 14
//     build._ISUB_();             // 16
//     build._CALL_(1);            // 17
//     build._IADD_();             // 19
//     build._RETURN_();           // 20

//     size_t main_offset = bytecode->size();

//     // main()
//     build._BIPUSH_(n);         // 21
//     build._CALL_(1);            // 23
//     build._RETURN_();           // 25

//     // add main(): // main allways has entrance point in zero
//     // 0 - main, 1 - fibanachi
//     Function MAIN(main_offset);
//     functions.push_back(MAIN);

//     // add fib(int):
//     Function FIB(0, static_cast<int>(0));
//     functions.push_back(FIB);
// };

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